#include "DataNode.hpp"
#include <chrono>
#include <gtest/gtest.h>

using namespace std;

TEST(DataTest, Initialization) { auto source = DataNode<int>(); }

TEST(DataTest, AddSource) {
  std::shared_ptr<DataNode<int>> root = std::make_shared<DataNode<int>>();
  auto second = std::make_shared<DataNode<int>>();
  ASSERT_EQ(root->get_pull_nodes().size(), 0);
  root->add_pull_node(second);
  ASSERT_EQ(root->get_pull_nodes().size(), 1);
  ASSERT_EQ(root->get_push_nodes().size(), 0);
  second->add_push_node(root);
  ASSERT_EQ(second->get_push_nodes().size(), 1);
}