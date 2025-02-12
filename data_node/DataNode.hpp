#pragma once

#include <memory>
#include <time.h>
#include <vector>

class IDataNode;

typedef std::shared_ptr<IDataNode> DataNodeShrPtr;
typedef std::weak_ptr<IDataNode> DataNodeWeakPtr;

class IDataNode {
  std::vector<DataNodeShrPtr> _upstream_nodes;
  std::vector<DataNodeWeakPtr> _downstream_nodes;
  friend std::shared_ptr<std::vector<DataNodeShrPtr>>
  get_leaf_nodes(std::shared_ptr<IDataNode> node,
                 std::shared_ptr<std::vector<DataNodeShrPtr>> leaf_nodes);

public:
  IDataNode() : _upstream_nodes(), _downstream_nodes() {}
  std::vector<DataNodeShrPtr> get_upstream_nodes() { return _upstream_nodes; }
  std::vector<DataNodeWeakPtr> get_downstream_nodes() { return _downstream_nodes; }
  void add_upstream_node(DataNodeShrPtr data) { _upstream_nodes.push_back(data); }
  void add_downstream_node(DataNodeWeakPtr data) { _downstream_nodes.push_back(data); }
};

template <typename T> class DataNode : public IDataNode {
  std::vector<T> _data;

public:
  virtual std::vector<T> get_data() { return _data; };
};
