#include "DataNode.hpp"

std::shared_ptr<std::vector<DataNodeShrPtr>>
get_leaf_nodes(std::shared_ptr<IDataNode> node,
               std::shared_ptr<std::vector<DataNodeShrPtr>> leaf_nodes = nullptr) {
  if (leaf_nodes == nullptr) {
    leaf_nodes = std::make_shared<std::vector<DataNodeShrPtr>>();
  }
  for (auto &upstream_node : node->_upstream_nodes) {
  }
  return leaf_nodes;
}
