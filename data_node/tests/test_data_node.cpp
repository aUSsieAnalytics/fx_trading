#include "DataNode.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(DataTest, Initialization) {
  DataNode<int> source = DataNode<int>();
  DataNode<int> hi_node = DataNode<int>("hi");
  for (int i = 0; i < 100; i++) {
    hi_node = DataNode<int>(i, "hi");
  }
  std::string hash = source.get_hash();
  ASSERT_EQ(hash, DataNode<int>().get_hash());
  ASSERT_EQ(hash, sha256("IDataNode"));
  ASSERT_NE(hash, hi_node.get_hash());
  ASSERT_EQ(DataNode<int>("hi").get_hash(), sha256("IDataNodehi"));
}

TEST(DataTest, AddSource) {
  auto root = make_shared<DataNode<int>>();
  auto second = make_shared<DataNode<double>>();
  ASSERT_EQ(root->get_upstream_nodes().size(), 0);
  root->add_upstream_node(second);
  ASSERT_EQ(root->get_upstream_nodes().size(), 1);
  ASSERT_EQ(root->get_downstream_nodes().size(), 0);
  ASSERT_EQ(second->get_downstream_nodes().size(), 1);
}

TEST(DataTest, CollectLeafNodes) {
  auto root = make_shared<DataNode<int>>();
  auto leaf1 = make_shared<DataNode<double>>();
  auto second = make_shared<DataNode<int>>();
  root->add_upstream_node(second);
  auto leaves = get_leaf_nodes(root);
  ASSERT_EQ(leaves->size(), 1);
  ASSERT_EQ(get_leaf_nodes(leaf1)->size(), 1);
}