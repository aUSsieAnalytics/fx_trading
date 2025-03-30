#include "stonex.h"
#include "stonex_mock.hpp"
#include "trading_types.hpp"
#include <cpr/cpr.h>
#include <ctime>
#include <gtest/gtest.h>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

TEST_F(StoneXTest, TestInitializeSession) {

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

  EXPECT_EQ(StoneX::AccountCredentials::initialized, false);

  StoneX::initialize_session();
  EXPECT_EQ(StoneX::AccountCredentials::initialized, true);
}
