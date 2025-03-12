#include "stonex.h"
#include "trading_types.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(StoneXTest, TestAccountState) {
  StoneX::initialize_session();
  auto account_info = StoneX::get_account_info();
  std::cout << json(account_info) << "\n";
  auto margin_summary = StoneX::get_account_margin();
  std::cout << json(margin_summary) << "\n";
  auto market = StoneX::get_market_info(ForexPair::EURUSD);
  std::cout << json(market) << "\n";
}