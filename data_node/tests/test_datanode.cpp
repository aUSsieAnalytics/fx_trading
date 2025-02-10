#include "DataNode.hpp"
#include <chrono>
#include <gtest/gtest.h>

using namespace std;

TEST(DataTest, Initialization) { auto source = DataNode<int>(); }

// TEST(DataTest, AddSource) {
//   auto root = std::make_shared<DataNode<int>>();
//   auto second = std::make_shared<DataNode<int>>();
//   ASSERT_EQ(root->get_pull_data().size(), 0);
//   root->add_pull_data(second);
//   ASSERT_EQ(root->get_pull_data().size(), 1);
//   ASSERT_EQ(root->get_push_data().size(), 0);
//   second->add_push_data(root);
//   ASSERT_EQ(second->get_push_data().size(), 1);
// }