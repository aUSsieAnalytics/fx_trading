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
  void add_to_hash_string(T t = "", Args... args) {
    std::ostringstream oss;
    oss << t;
    std::string as_string = oss.str();
    if (as_string == "") {
      return;
    }
    _hash_string += as_string;
    add_to_hash_string(args...);
  }

public:
  DataNodeWeakPtr get_weak_ptr() { return shared_from_this(); };
  template <class... Args>
  IDataNode(Args... args) : _upstream_nodes(), _downstream_nodes(), _class_name(__func__) {
    add_to_hash_string(_class_name, args...);
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

template <typename T> class DataNode : public IDataNode {
  std::vector<T> _data;

public:
  template <class... Args> DataNode(Args... args) : IDataNode(args...), _data(){};
  virtual std::vector<T> get_data() { return _data; };
};
