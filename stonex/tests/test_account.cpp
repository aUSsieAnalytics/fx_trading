#include "stonex.h"
#include "trading_types.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST(StoneXTest, TestStoneX) {
  StoneX::initialize_session();
  auto account_info = StoneX::get_account_info();
  // std::cout << json(account_info) << "\n";
  auto margin_summary = StoneX::get_account_margin();
  // std::cout << json(margin_summary) << "\n";
  auto market = StoneX::get_market_info(ForexPair::EURUSD);
  // std::cout << json(market) << "\n";
  auto candles = StoneX::get_latest_price_bars(ForexPair::EURUSD, 20, 15, CandlePeriodUnit::MINUTE,
                                               PriceType::MID);

  for (int i = 0; i < 100; i++) {
    candles = StoneX::get_latest_price_bars(ForexPair::EURUSD, 20, 15, CandlePeriodUnit::MINUTE,
                                            PriceType::MID);
  }
  // std::cout << json(candles) << "\n";
}