#include "AccountState.hpp"
#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include "orders.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace DataNodes;

TEST_F(DataNodeTest, TestAccountState) {
  auto node = DataNode<AccountStateNode>::create(Broker::FOREXCOM);
  node->calculate();
}