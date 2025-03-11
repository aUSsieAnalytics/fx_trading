#include "AccountState.hpp"
#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include "orders.hpp"
#include "stonex.h"
#include <gtest/gtest.h>
#include <iostream>

using namespace DataNodes;

TEST_F(DataNodeTest, TestAccountState) {
  StoneX::initialize_session();
  auto node = DataNode<AccountStateNode>::create(Broker::FOREXCOM);
  node->logger->serialize();
  node->calculate();
}