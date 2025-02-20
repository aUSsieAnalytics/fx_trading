#pragma once

#include "sha256.hpp"
#include <memory>
#include <mutex>
#include <sstream>
#include <unordered_map>
#include <vector>

class IDataNode;
template <typename ClassName = IDataNode, typename T = double> class DataNode;

typedef std::shared_ptr<IDataNode> DataNodeShrPtr;
typedef std::weak_ptr<IDataNode> DataNodeWeakPtr;

class DataStore {
  std::unordered_map<std::string, std::shared_ptr<void>> _store;

public:
  DataStore() : _store() {};

  template <typename ClassName, typename T>
  void put_in_store(DataNode<ClassName, T> *node, std::shared_ptr<std::vector<T>> data) {
    _store[node->get_hash()] = data;
  }

  template <typename ClassName, typename T>
  std::shared_ptr<std::vector<T>> retrieve(DataNode<ClassName, T> *node) {
    if (_store.find(node->get_hash()) != _store.end()) {
      return std::static_pointer_cast<std::vector<T>>(_store[node->get_hash()]);
    }
    return nullptr;
  };
};

class IDataNode : public std::enable_shared_from_this<IDataNode> {
  static inline std::mutex _scope_lock;
  static inline std::string _scope;
  std::string _class_scope;
  std::string _class_name;
  std::vector<DataNodeShrPtr> _upstream_nodes;
  std::vector<DataNodeWeakPtr> _downstream_nodes;
  std::string _hash;
  std::string _hash_string;

  friend std::ostream &operator<<(std::ostream &stream, IDataNode &node) {
    return stream << node._hash_string;
  }
  friend std::ostream &operator<<(std::ostream &stream, DataNodeShrPtr node) {
    return stream << node->_hash_string;
  }
  friend std::ostream &operator<<(std::ostream &stream, DataNodeWeakPtr node) {
    auto real_ptr = node.lock();
    if (real_ptr) {
      stream << real_ptr->_hash_string;
    }
    return stream;
  }

  friend std::shared_ptr<std::vector<DataNodeShrPtr>>
  get_leaf_nodes(std::shared_ptr<IDataNode> node,
                 std::shared_ptr<std::vector<DataNodeShrPtr>> leaf_nodes = nullptr) {
    {
      if (leaf_nodes == nullptr) {
        leaf_nodes = std::make_shared<std::vector<DataNodeShrPtr>>();
      }
      if (node->_upstream_nodes.size() == 0) {
        leaf_nodes->push_back(node);
      }
      for (auto &upstream_node : node->_upstream_nodes) {
        get_leaf_nodes(upstream_node, leaf_nodes);
      }
      return leaf_nodes;
    }
  }

  template <typename T = std::string, typename... Args>
  void create_hash_string(T t = "", Args... args) {
    std::ostringstream oss;
    oss << t;
    if (oss.str().size() == 0) {
      return;
    }
    if (sizeof...(args) != 0) {
      oss << ", ";
    };
    std::string as_string = oss.str();
    _hash_string += as_string;
    create_hash_string(args...);
  }

protected:
  static inline DataStore _data_store;

public:
  class ScopeLock {
  public:
    ScopeLock(std::string scope) {
      _scope_lock.lock();
      _scope = scope;
    }
    ~ScopeLock() {
      _scope = "";
      _scope_lock.unlock();
    }
  };
  DataNodeWeakPtr get_weak_ptr() { return shared_from_this(); };

  template <class... Args>
  IDataNode(std::string class_name, Args... args)
      : _upstream_nodes(), _downstream_nodes(), _class_name(class_name) {
    _class_scope = _scope;
    _scope == "" ? _hash_string = "" : _hash_string = _class_scope + ": ";
    _hash_string += _class_name + ": ";
    create_hash_string(args...);
    _hash = sha256(_hash_string);
  }

  std::vector<DataNodeShrPtr> get_upstream_nodes() { return _upstream_nodes; }

  std::vector<DataNodeWeakPtr> get_downstream_nodes() { return _downstream_nodes; }
  std::string get_scope() { return _class_scope; }
  void add_upstream_node(DataNodeShrPtr data) {
    _upstream_nodes.push_back(data);
    data->_downstream_nodes.push_back(get_weak_ptr());
  }

  std::string get_hash() { return _hash; }
};

template <typename ClassName, typename T> class DataNode : public IDataNode {
  std::vector<T> _data;
  void _calculate() { _data_store.put_in_store(calculate()); }

protected:
  template <class... Args>
  DataNode(std::string class_name = "", Args... args) : IDataNode(class_name, args...), _data(){};

public:
  virtual ~DataNode() = default;
  std::shared_ptr<std::vector<T>> get_data() {
    auto data = _data_store.retrieve(this);
    if (!data) {
      _data_store.put_in_store(this, calculate());
      data = _data_store.retrieve(this);
    }
    return data;
  }

  virtual std::shared_ptr<std::vector<T>> calculate() { return nullptr; }

  template <class... Args> static std::shared_ptr<ClassName> create(Args... args) {
    return std::make_shared<ClassName>(ClassName(args...));
  }
};
