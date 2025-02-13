#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

class IDataNode;

typedef std::shared_ptr<IDataNode> DataNodeShrPtr;
typedef std::weak_ptr<IDataNode> DataNodeWeakPtr;

class IDataNode : public std::enable_shared_from_this<IDataNode> {
  std::vector<DataNodeShrPtr> _upstream_nodes;
  std::vector<DataNodeWeakPtr> _downstream_nodes;
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

public:
  DataNodeWeakPtr get_weak_ptr() { return shared_from_this(); };
  IDataNode() : _upstream_nodes(), _downstream_nodes() {}
  std::vector<DataNodeShrPtr> get_upstream_nodes() { return _upstream_nodes; }
  std::vector<DataNodeWeakPtr> get_downstream_nodes() { return _downstream_nodes; }
  void add_upstream_node(DataNodeShrPtr data) {
    _upstream_nodes.push_back(data);
    data->_downstream_nodes.push_back(get_weak_ptr());
  }
};

template <typename T> class DataNode : public IDataNode {
  std::vector<T> _data;

public:
  DataNode() : _data() {};
  virtual std::vector<T> get_data() { return _data; };
};
