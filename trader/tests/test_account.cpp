#include "AccountState.hpp"
#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include "orders.hpp"
#include "stonex.h"
#include <gtest/gtest.h>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace DataNodes;
using json = nlohmann::json;

TEST_F(DataNodeTest, TestAccountState) {
  StoneX::initialize_session();
  auto node = DataNode<AccountStateNode>::create(Broker::FOREXCOM);
  node->calculate();
  node->logger->info("account id: " + std::to_string(StoneX::AccountCredentials::account_id));
  auto account_info = StoneX::get_account_info();
  node->logger->info(json(account_info).dump());
  auto margin_summary = StoneX::get_account_margin();
  node->logger->info(json(margin_summary).dump());
}