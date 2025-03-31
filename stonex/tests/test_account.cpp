#include "stonex.h"
#include "stonex_mock.hpp"
#include "trading_types.hpp"
#include <cpr/cpr.h>
#include <ctime>
#include <gtest/gtest.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST_F(StoneXTest, TestAuthorizeAccount) {
  StoneX::AccountCredentials::authorized = false;

  EXPECT_EQ(StoneX::AccountCredentials::authorized, false);
  EXPECT_EQ(StoneX::authorize_stonex(), true);
  EXPECT_EQ(StoneX::AccountCredentials::authorized, true);
  EXPECT_EQ(StoneX::authorize_stonex(), true);

  StoneX::AccountCredentials::authorized = false;

  unsetenv("STONEX_USER");
  EXPECT_EQ(StoneX::authorize_stonex(), false);
  EXPECT_EQ(StoneX::AccountCredentials::authorized, false);
  setenv("STONEX_USER", "TESTING", 1);

  unsetenv("STONEX_PASS");
  EXPECT_EQ(StoneX::authorize_stonex(), false);
  EXPECT_EQ(StoneX::AccountCredentials::authorized, false);
  setenv("STONEX_PASS", "TESTING", 1);

  unsetenv("STONEX_APPKEY");
  EXPECT_EQ(StoneX::authorize_stonex(), false);
  EXPECT_EQ(StoneX::AccountCredentials::authorized, false);
  setenv("STONEX_APPKEY", "TESTING", 1);
}

TEST_F(StoneXTest, TestGetAccountInfoBadAuth) {
  StoneX::AccountCredentials::authorized = false;
  unsetenv("STONEX_USER");
  EXPECT_THROW(
      {
        try {
          StoneX::get_account_info();
        } catch (const std::runtime_error &e) {
          EXPECT_STREQ("Could not authorize session.", e.what());
          throw;
        }
      },
      std::runtime_error);
  setenv("STONEX_USER", "TESTING", 1);
}

TEST_F(StoneXTest, TestGetAccountInfoGoodResp) {
  StoneX::AccountCredentials::authorized = true;

  StoneX::AccountResult account_resp;
  account_resp.tradingAccounts.push_back(StoneX::ApiTradingAccountDTO{
      1234, 456, "test_code", "test_status", "test_type", "test_name"});

  svr->Get("/UserAccount/ClientAndTradingAccount",
           [account_resp](const httplib::Request &req, httplib::Response &res) {
             res.set_content(json(account_resp).dump(), "application/json");
           });
  StoneX::AccountResult got_resp = StoneX::get_account_info();
  EXPECT_EQ(got_resp.tradingAccounts[0].clientAccountId,
            account_resp.tradingAccounts[0].clientAccountId);
}

TEST_F(StoneXTest, TestInitializeSessionGoodAuth) {
  StoneX::ApiLogOnResponseDTO sess_resp;
  sess_resp.session = "1234567890";
  // Configure mock responses
  svr->Post("/Session", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_content(json(sess_resp).dump(), "application/json");
  });

  StoneX::AccountResult account_resp;
  account_resp.tradingAccounts.push_back(StoneX::ApiTradingAccountDTO{
      1234, 456, "test_code", "test_status", "test_type", "test_name"});

  svr->Get("/UserAccount/ClientAndTradingAccount",
           [account_resp](const httplib::Request &req, httplib::Response &res) {
             res.set_content(json(account_resp).dump(), "application/json");
           });

  StoneX::AccountCredentials::authorized = false;
  StoneX::AccountCredentials::initialized = false;
  EXPECT_EQ(StoneX::AccountCredentials::initialized, false);
  StoneX::initialize_session();
  EXPECT_EQ(StoneX::AccountCredentials::initialized, true);

  StoneX::AccountCredentials::authorized = true;
  StoneX::AccountCredentials::initialized = false;
  EXPECT_EQ(StoneX::AccountCredentials::initialized, false);
  StoneX::initialize_session();
  EXPECT_EQ(StoneX::AccountCredentials::initialized, true);
}

TEST_F(StoneXTest, TestInitializeSessionBadAuth) {

  StoneX::ApiLogOnResponseDTO sess_resp;
  sess_resp.session = "1234567890";
  // Configure mock responses
  svr->Post("/Session", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_content(json(sess_resp).dump(), "application/json");
  });

  StoneX::AccountResult account_resp;
  account_resp.tradingAccounts.push_back(StoneX::ApiTradingAccountDTO{
      1234, 456, "test_code", "test_status", "test_type", "test_name"});

  svr->Get("/UserAccount/ClientAndTradingAccount",
           [account_resp](const httplib::Request &req, httplib::Response &res) {
             res.set_content(json(account_resp).dump(), "application/json");
           });

  StoneX::AccountCredentials::authorized = false;
  StoneX::AccountCredentials::initialized = false;
  unsetenv("STONEX_USER");
  EXPECT_EQ(StoneX::initialize_session(), false);
  setenv("STONEX_USER", "TESTING", 1);
  EXPECT_EQ(StoneX::AccountCredentials::initialized, false);
}

TEST_F(StoneXTest, TestInitializeSessionBadResp) {

  StoneX::ApiLogOnResponseDTO sess_resp;
  sess_resp.session = "1234567890";
  // Configure mock responses
  svr->Post("/Session", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_content(json(sess_resp).dump(), "application/json");
    res.status = 300;
  });

  StoneX::AccountCredentials::authorized = true;
  StoneX::AccountCredentials::initialized = false;
  unsetenv("STONEX_USER");
  EXPECT_EQ(StoneX::initialize_session(), false);
  setenv("STONEX_USER", "TESTING", 1);
  EXPECT_EQ(StoneX::AccountCredentials::initialized, false);
}

TEST_F(StoneXTest, TestGetAccountMargin) {
  StoneX::AccountCredentials::authorized = true;
  StoneX::AccountCredentials::initialized = true;
  StoneX::AccountCredentials::account_id = 1234;

  StoneX::ClientAccountMarginResponseDTO resp;
  resp.cash = 6542;
  svr->Get("/margin/clientAccountMargin", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_content(json(resp).dump(), "application/json");
  });
  EXPECT_EQ(StoneX::get_account_margin().cash, resp.cash);
}

TEST_F(StoneXTest, TestGetAccountMarginBadCreds) {
  StoneX::AccountCredentials::authorized = false;
  StoneX::AccountCredentials::initialized = false;

  unsetenv("STONEX_USER");
  StoneX::AccountCredentials::account_id = 0;
  EXPECT_THROW(
      {
        try {
          StoneX::get_account_margin();
        } catch (const std::runtime_error &e) {
          EXPECT_STREQ("Could not initialize the session.", e.what());
          throw;
        }
      },
      std::runtime_error);
  setenv("STONEX_USER", "TESTING", 1);
}

TEST_F(StoneXTest, TestGetMarketInfoBadCreds) {
  StoneX::AccountCredentials::initialized = false;
  StoneX::AccountCredentials::account_id = 0;
  unsetenv("STONEX_USER");
  EXPECT_THROW(
      {
        try {
          StoneX::get_market_info(ForexPair::EURUSD);
        } catch (const std::runtime_error &e) {
          EXPECT_STREQ("Could not initialize the session.", e.what());
          throw;
        }
      },
      std::runtime_error);
  setenv("STONEX_USER", "TESTING", 1);
}

TEST_F(StoneXTest, TestGetMarketInfoAlreadyExists) {
  StoneX::ApiMarketInformationDTO info;
  info.marketId = 2020;
  StoneX::markets["EURUSD"] = info;
  auto from_store = StoneX::get_market_info(ForexPair::EURUSD);
  EXPECT_EQ(from_store.marketId, info.marketId);
}

TEST_F(StoneXTest, TestGetMarketInfo) {
  StoneX::ApiMarketInformationDTO info;
  info.marketId = 2020;
  StoneX::FullMarketInformationSearchWithTagsResponseDTO resp;
  resp.marketInformation.push_back(info);
  svr->Get("/market/fullSearchWithTags", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_content(json(resp).dump(), "application/json");
  });

  StoneX::AccountCredentials::initialized = true;
  StoneX::AccountCredentials::account_id = 10;
  auto retrieved = StoneX::get_market_info(ForexPair::AUDCAD);
  EXPECT_EQ(retrieved.marketId, info.marketId);
  EXPECT_EQ(StoneX::markets["AUDCAD"].marketId, 2020);
}

TEST_F(StoneXTest, TestGetLatestPriceBars) {
  StoneX::GetPriceBarResponseDTO bars;
  StoneX::PriceBarDTO bar;
  bar.high = 45;
  bars.partialPriceBar.high = 77;
  bars.priceBars.push_back(bar);
  StoneX::ApiMarketInformationDTO info;
  info.marketId = 2020;
  StoneX::FullMarketInformationSearchWithTagsResponseDTO resp;
  resp.marketInformation.push_back(info);
  StoneX::markets["AUDCAD"] = info;

  svr->Get("/market/2020/barhistory", [&](const httplib::Request &req, httplib::Response &res) {
    EXPECT_EQ(req.params.find("interval")->second, "MINUTE");
    EXPECT_EQ(req.params.find("PriceType")->second, "MID");
    res.set_content(json(bars).dump(), "application/json");
  });

  auto retreived = StoneX::get_latest_price_bars(ForexPair::AUDCAD, 1, 1, CandlePeriodUnit::MINUTE);
  EXPECT_EQ(retreived.partialPriceBar.high, bars.partialPriceBar.high);
  EXPECT_EQ(retreived.priceBars[0].high, bars.priceBars[0].high);
}

TEST_F(StoneXTest, TestGetPriceBarsBetween) {
  StoneX::GetPriceBarResponseDTO bars;
  StoneX::PriceBarDTO bar;
  bar.high = 45;
  bars.partialPriceBar.high = 77;
  bars.priceBars.push_back(bar);
  StoneX::ApiMarketInformationDTO info;
  info.marketId = 2020;
  StoneX::FullMarketInformationSearchWithTagsResponseDTO resp;
  resp.marketInformation.push_back(info);
  StoneX::markets["AUDCAD"] = info;

  svr->Get("/market/2020/barhistorybetween",
           [&](const httplib::Request &req, httplib::Response &res) {
             EXPECT_EQ(req.params.find("interval")->second, "MINUTE");
             res.set_content(json(bars).dump(), "application/json");
           });

  std::chrono::year_month_day ymd = std::chrono::July / 7 / 2024;
  std::chrono::sys_days sd = ymd;
  std::chrono::system_clock::time_point tp = sd;
  tp += std::chrono::hours{12} + std::chrono::minutes{0} + std::chrono::seconds{0};
  auto from_unix_time = std::chrono::system_clock::to_time_t(tp);
  auto to_unix_time = std::chrono::system_clock::to_time_t(tp + std::chrono::hours{30});
  auto retreived = StoneX::get_price_bars_between(ForexPair::AUDCAD, from_unix_time, to_unix_time,
                                                  15, CandlePeriodUnit::MINUTE, PriceType::MID);

  EXPECT_EQ(retreived.partialPriceBar.high, bars.partialPriceBar.high);
  EXPECT_EQ(retreived.priceBars[0].high, bars.priceBars[0].high);
}