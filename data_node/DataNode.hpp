#pragma once

#include "Logger.hpp"
#include "sha256.hpp"
#include "uuid.hpp"
#include <array>
#include <cstdio>
#include <functional>
#include <memory>
#include <mutex>
#include <regex>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

template <typename T> std::string exec(const T *cmd) {
  std::array<char, 256> buffer;
  std::string result;
  std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
  // if (!pipe) {
  //   throw std::runtime_error("popen() failed!");
  // }
  while (fgets(buffer.data(), static_cast<int>(buffer.size()), pipe.get()) != nullptr) {
    result += buffer.data();
  }
  return result;
}

namespace DataNodes {

template <typename T = std::string> std::string remove_data_node_namespace_str(std::string str) {
  std::regex pattern("DataNodes::");
  std::string result = std::regex_replace(str, pattern, "");
  result.pop_back();
  return result;
}

template <typename T> std::ostream &operator<<(std::ostream &stream, const std::vector<T> &vector) {
  std::ostringstream oss;
  for (auto &entry : vector) {
    oss << entry;
  }
  return stream << sha256(oss.str());
}

template <typename T = std::string, typename... Args>
std::string create_hash_string(std::string hash_string = "", T t = "", Args... args) {
  std::ostringstream oss;
  oss << t;
  if (oss.str().size() == 0) {
    return hash_string;
  }
  if (sizeof...(args) != 0) {
    oss << ", ";
  };
  std::string as_string = oss.str();
  return create_hash_string(hash_string + as_string, args...);
}

class IDataNode;
template <typename ClassName = IDataNode, typename T = double> class DataNode;
template <typename T> class OutputNode;

typedef std::shared_ptr<IDataNode> DataNodeShrPtr;
typedef std::weak_ptr<IDataNode> DataNodeWeakPtr;

template <typename X, typename Y>
std::ostream &operator<<(std::ostream &stream, const std::shared_ptr<DataNode<X, Y>> &node) {
  return stream << "DataNode{" << node->get_hash() << "}";
}

class DataStore {
  std::unordered_map<std::string, std::shared_ptr<void>> _store;

public:
  ~DataStore() { _store.clear(); }
  DataStore() : _store() {};

  template <typename ClassName, typename T> void clear_data(DataNode<ClassName, T> *node) {
    if (_store.size() == 0) {
      return;
    }
    if (_store.find(node->get_hash()) != _store.end()) {
      _store.erase(node->get_hash());
    }
  }

private:
  template <typename ClassName, typename T> friend class DataNode;

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
  static inline std::unordered_map<std::string, DataNodeShrPtr> __registry__;
  static inline std::mutex _scope_lock;
  static inline std::string _scope;
  static inline std::shared_ptr<StructuredLogger> _base_logger = std::make_shared<StructuredLogger>(
      "DataNode", std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
  std::string _class_scope;
  std::string _class_name;
  std::vector<DataNodeShrPtr> _upstream_nodes;
  std::vector<std::shared_ptr<std::string>> _downstream_node_hashes;
  std::vector<DataNodeShrPtr> _output_nodes;
  std::weak_ptr<std::string> _parent_hash;
  std::function<void(std::shared_ptr<void> onode)> _parent_calc;
  std::shared_ptr<std::string> _hash;
  std::string _hash_string;

  template <typename ClassName, typename T> friend class DataNode;

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

protected:
  static inline DataStore _data_store;

public:
  std::shared_ptr<StructuredLogger> logger;

  static void clear_registry() { IDataNode::__registry__.clear(); }

  static void set_logger(std::shared_ptr<StructuredLogger> logger) {
    IDataNode::_base_logger = logger;
  }

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
  IDataNode(Args... args)
      : _upstream_nodes(), _downstream_node_hashes(), _hash(new std::string("")) {
    logger = IDataNode::_base_logger;
  }

  std::vector<DataNodeShrPtr> get_upstream_nodes() { return _upstream_nodes; }

  std::vector<DataNodeWeakPtr> get_downstream_nodes() {
    std::vector<DataNodeWeakPtr> downstream_nodes = {};
    for (auto &_n_hash : _downstream_node_hashes) {
      downstream_nodes.push_back(IDataNode::__registry__[*_n_hash]);
    }
    return downstream_nodes;
  }

  std::string get_scope() { return _class_scope; }

  template <typename ClassName>
  std::shared_ptr<ClassName> add_upstream_node(std::shared_ptr<ClassName> node) {
    _upstream_nodes.push_back(node);
    node->_downstream_node_hashes.push_back(_hash);
    return node;
  }

  std::string get_hash() { return *_hash; }
};

template <typename ClassName, typename T> class DataNode : public IDataNode {
public:
  static inline const std::string type_id = remove_data_node_namespace_str(
      exec(("c++filt -t " + std::string(typeid(DataNode<ClassName, T>).name())).data()));

  template <class... Args> DataNode<ClassName, T>(Args... args) : IDataNode(args...) {
    logger = IDataNode::_base_logger->bind();
    logger->set_name(DataNode<ClassName, T>::type_id);
  };

  friend class IDataNode;

  template <typename A> std::shared_ptr<OutputNode<A>> register_output_node() {
    std::string hash_string;
    std::string identifier = uuid::generate_uuid_v4();
    _scope == "" ? hash_string = "" : hash_string = _scope + ": ";
    hash_string += "(" + DataNode<ClassName, T>::type_id + ")" + ": ";
    hash_string = create_hash_string(hash_string, identifier);
    auto hash_val = sha256(hash_string);
    auto output_node = std::make_shared<OutputNode<A>>(OutputNode<A>());
    output_node->_hash->assign(hash_val);
    output_node->logger = output_node->logger->bind("hash", hash_val, "hash_string", hash_string);
    output_node->_hash_string = hash_string;
    output_node->_class_scope = _scope;

    _output_nodes.push_back(output_node);
    output_node->_parent_hash = this->_hash;
    output_node->_parent_calc = [](std::shared_ptr<void> onode) {
      auto curr_node = std::static_pointer_cast<IDataNode>(onode);
      auto parent_hash = std::static_pointer_cast<IDataNode>(onode)->_parent_hash.lock();
      auto parent =
          std::static_pointer_cast<DataNode<ClassName, T>>(IDataNode::__registry__[*parent_hash]);
      parent->logger->debug("calculating");
      parent->calculate();
    };
    return output_node;
  }

  virtual ~DataNode() {
    if (this->_hash != nullptr) {
      _data_store.clear_data(this);
    }
  };

  void set_data(std::vector<T> &data) {
    _data_store.put_in_store(this, std::make_shared<std::vector<T>>(data));
  }

  std::vector<T> get_data() {
    auto data = _data_store.retrieve(this);
    if (!data) {
      if (this->_parent_hash.lock()) {
        this->_parent_calc(shared_from_this());
      } else {
        this->logger->debug("calculating");
        calculate();
      }
      data = _data_store.retrieve(this);
    }
    return std::vector<T>(*data);
  }

  virtual void calculate() {
    if (_parent_hash.lock()) {
      _parent_calc(shared_from_this());
    }
  }

  template <class... Args> static std::shared_ptr<ClassName> create(Args... args) {
    std::string hash_string;
    _scope == "" ? hash_string = "" : hash_string = _scope + ": ";
    hash_string += "(" + DataNode<ClassName, T>::type_id + ")" + ": ";
    hash_string = create_hash_string(hash_string, args...);
    auto hash_val = sha256(hash_string);
    if (IDataNode::__registry__.find(hash_val) != IDataNode::__registry__.end()) {
      return std::static_pointer_cast<ClassName>(IDataNode::__registry__[hash_val]);
    }
    auto new_node = std::make_shared<ClassName>(ClassName(args...));
    new_node->logger = new_node->logger->bind("hash", hash_val, "hash_string", hash_string);
    new_node->_hash->assign(hash_val);
    new_node->_hash_string = hash_string;
    new_node->_class_scope = _scope;
    IDataNode::__registry__[new_node->get_hash()] = new_node;
    return new_node;
  }
};

template <typename T> class OutputNode : public DataNode<IDataNode, T> {
public:
  template <class... Args> OutputNode(Args... args) : DataNode<IDataNode, T>(args...) {}
};

} // namespace DataNodes