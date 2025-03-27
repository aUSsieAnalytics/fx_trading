#include "stonex.h"
#include "trading_types.hpp"
#include <ctime>
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
  // std::cout << json(candles) << "\n";

  std::chrono::year_month_day ymd = std::chrono::July / 7 / 2024;
  std::chrono::sys_days sd = ymd;
  std::chrono::system_clock::time_point tp = sd;
  tp += std::chrono::hours{12} + std::chrono::minutes{0} + std::chrono::seconds{0};
  auto from_unix_time = std::chrono::system_clock::to_time_t(tp);
  auto to_unix_time = std::chrono::system_clock::to_time_t(tp + std::chrono::hours{30});
  auto resp = StoneX::get_price_bars_between(ForexPair::EURUSD, from_unix_time, to_unix_time, 15,
                                             CandlePeriodUnit::MINUTE, PriceType::MID);
}