#include "DataNode.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(DataTest, Initialization) {
  auto source = DataNode<>::create("DataNode");
  auto hi_node = DataNode<>::create("DataNode", "hi");
  for (int i = 0; i < 100; i++) {
    hi_node = DataNode<>::create("DataNode", i, "hi");
  }
  string hash = source->get_hash();
  ASSERT_EQ(hash, DataNode<>::create("DataNode")->get_hash());
  ASSERT_EQ(hash, sha256("DataNode: "));
  ASSERT_NE(hash, hi_node->get_hash());
  ASSERT_EQ(DataNode<>::create("DataNode", "hi")->get_hash(), sha256("DataNode: hi"));
  {
    // test scoping
    auto x = IDataNode::ScopeLock("local");
    ASSERT_NE(DataNode<>::create("DataNode", "hi")->get_hash(), sha256("DataNode: hi"));
    ASSERT_EQ(DataNode<>::create("DataNode", "hi")->get_hash(), sha256("local: DataNode: hi"));
  }
  // check that scope was cleared
  ASSERT_EQ(DataNode<>::create("DataNode", "hi")->get_hash(), sha256("DataNode: hi"));
}

TEST(DataTest, AddSource) {
  auto root = DataNode<>::create("DataNode");
  auto second = DataNode<IDataNode, double>::create("DataNode");
  ASSERT_EQ(root->get_upstream_nodes().size(), 0);
  root->add_upstream_node(second);
  ASSERT_EQ(root->get_upstream_nodes().size(), 1);
  ASSERT_EQ(root->get_downstream_nodes().size(), 0);
  ASSERT_EQ(second->get_downstream_nodes().size(), 1);
}

TEST(DataTest, CollectLeafNodes) {
  auto root = DataNode<>::create("DataNode");
  auto leaf1 = DataNode<IDataNode, double>::create("DataNode");
  auto second = DataNode<>::create("DataNode");
  root->add_upstream_node(second);
  auto leaves = get_leaf_nodes(root);
  ASSERT_EQ(leaves->size(), 1);
  ASSERT_EQ(get_leaf_nodes(leaf1)->size(), 1);
}