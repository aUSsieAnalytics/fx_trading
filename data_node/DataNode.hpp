#pragma once

#include "sha256.hpp"
#include <memory>
#include <sstream>
#include <unordered_map>
#include <vector>

class IDataNode;

typedef std::shared_ptr<IDataNode> DataNodeShrPtr;
typedef std::weak_ptr<IDataNode> DataNodeWeakPtr;

class IDataNode : public std::enable_shared_from_this<IDataNode> {
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

public:
  DataNodeWeakPtr get_weak_ptr() { return shared_from_this(); };

  template <class... Args>
  IDataNode(std::string class_name, Args... args)
      : _upstream_nodes(), _downstream_nodes(), _class_name(class_name) {
    _hash_string = _class_name + ": ";
    create_hash_string(args...);
    _hash = sha256(_hash_string);
  }

  std::vector<DataNodeShrPtr> get_upstream_nodes() { return _upstream_nodes; }

  std::vector<DataNodeWeakPtr> get_downstream_nodes() { return _downstream_nodes; }

  void add_upstream_node(DataNodeShrPtr data) {
    _upstream_nodes.push_back(data);
    data->_downstream_nodes.push_back(get_weak_ptr());
  }

  std::string get_hash() { return _hash; }
};

template <typename T, class ClassName = IDataNode> class DataNode : public IDataNode {
  std::vector<T> _data;

public:
  template <class... Args>
  DataNode(std::string class_name = "", Args... args) : IDataNode(class_name, args...), _data(){};
  virtual ~DataNode() = default;
  virtual std::vector<T> get_data() { return _data; };

  template <class... Args> static std::shared_ptr<DataNode<T, ClassName>> create(Args... args) {
    return std::make_shared<ClassName>(ClassName(args...));
  };
};
