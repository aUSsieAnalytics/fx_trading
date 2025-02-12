#include "DataNode.hpp"
#include <chrono>
#include <gtest/gtest.h>

using namespace std;

TEST(DataTest, Initialization) { auto source = DataNode<int>(); }

TEST(DataTest, AddSource) {
  auto root = std::make_shared<DataNode<int>>();
  auto second = std::make_shared<DataNode<int>>();
  ASSERT_EQ(root->get_upstream_nodes().size(), 0);
  root->add_upstream_node(second);
  ASSERT_EQ(root->get_upstream_nodes().size(), 1);
  ASSERT_EQ(root->get_downstream_nodes().size(), 0);
  second->add_downstream_node(root);
  ASSERT_EQ(second->get_downstream_nodes().size(), 1);
}