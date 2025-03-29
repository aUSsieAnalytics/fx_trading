#include "stonex.h"
#include "trading_types.hpp"
#include <cpr/cpr.h>
#include <ctime>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <httplib.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class StoneXRespTest : public ::testing::Test {
protected:
  httplib::Server svr;
  std::thread server_thread;

  void SetUp() override {
    setenv("STONEX_APPKEY", "TESTING", 1);
    setenv("STONEX_USER", "TESTING", 1);
    setenv("STONEX_PASS", "TESTING", 1);
    StoneX::base_url_ptr->assign("http://localhost:8080");
    StoneX::trading_url_ptr->assign("http://localhost:8080");

    // Bind the server before running it
    svr.bind_to_port("localhost", 8080);

    // Start the server in a separate thread
    server_thread = std::thread([this]() { svr.listen_after_bind(); });

    // Give the server time to start
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  void TearDown() override {
    // Stop the server and join the thread
    svr.stop();
    if (server_thread.joinable()) {
      server_thread.join();
    }
  }
};

TEST_F(StoneXRespTest, TestInitializeSession) {

  StoneX::ApiLogOnResponseDTO sess_resp;
  sess_resp.session = "1234567890";
  // Configure mock responses
  svr.Post("/Session", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_content(json(sess_resp).dump(), "application/json");
  });

  StoneX::AccountResult account_resp;
  account_resp.tradingAccounts.push_back(StoneX::ApiTradingAccountDTO{
      1234, 456, "test_code", "test_status", "test_type", "test_name"});

  svr.Get("/UserAccount/ClientAndTradingAccount",
          [account_resp](const httplib::Request &req, httplib::Response &res) {
            res.set_content(json(account_resp).dump(), "application/json");
          });

  EXPECT_EQ(StoneX::AccountCredentials::initialized, false);

  StoneX::initialize_session();
  EXPECT_EQ(StoneX::AccountCredentials::initialized, true);
}

// TEST(StoneXTest, TestStoneX) {
//   StoneX::session = std::make_shared<MockCprSession>();

//   StoneX::initialize_session();
//   auto account_info = StoneX::get_account_info();
//   // std::cout << json(account_info) << "\n";
//   auto margin_summary = StoneX::get_account_margin();
//   // std::cout << json(margin_summary) << "\n";
//   auto market = StoneX::get_market_info(ForexPair::EURUSD);
//   // std::cout << json(market) << "\n";
//   auto candles = StoneX::get_latest_price_bars(ForexPair::EURUSD, 20, 15,
//   CandlePeriodUnit::MINUTE,
//                                                PriceType::MID);
//   // std::cout << json(candles) << "\n";

//   std::chrono::year_month_day ymd = std::chrono::July / 7 / 2024;
//   std::chrono::sys_days sd = ymd;
//   std::chrono::system_clock::time_point tp = sd;
//   tp += std::chrono::hours{12} + std::chrono::minutes{0} + std::chrono::seconds{0};
//   auto from_unix_time = std::chrono::system_clock::to_time_t(tp);
//   auto to_unix_time = std::chrono::system_clock::to_time_t(tp + std::chrono::hours{30});
//   auto resp = StoneX::get_price_bars_between(ForexPair::EURUSD, from_unix_time, to_unix_time, 15,
//                                              CandlePeriodUnit::MINUTE, PriceType::MID);
// }