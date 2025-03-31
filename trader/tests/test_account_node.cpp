#include "AccountState.hpp"
#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include "httplib.h"
#include "nlohmann/json.hpp"
#include "stonex_mock.hpp"
#include "trading_types.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace DataNodes;
using json = nlohmann::json;

class StoneXDataNodeTest : public StoneXTest, public DataNodeTest {
protected:
  static void SetUpTestSuite() { StoneXTest::SetUpTestSuite(); }
  static void TearDownTestSuite() { StoneXTest::TearDownTestSuite(); }
  void SetUp() override {
    StoneXTest::SetUp();
    DataNodeTest::SetUp();
  }

  void TearDown() override {
    StoneXTest::TearDown();
    DataNodeTest::TearDown();
  }
};

TEST_F(StoneXDataNodeTest, TestAccountState) {
  StoneX::AccountCredentials::authorized = true;
  StoneX::AccountCredentials::initialized = true;
  StoneX::AccountCredentials::account_id = 1234;

  StoneX::ClientAccountMarginResponseDTO resp;
  resp.cash = 6542;
  svr->Get("/margin/clientAccountMargin", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_content(json(resp).dump(), "application/json");
  });

  auto node = DataNode<AccountStateNode>::create(Broker::FOREXCOM);
  node->calculate();
  node->logger->info(json(node->get_data()).dump());
  auto data = node->get_data();
  EXPECT_EQ(data.cash, resp.cash);
  node = DataNode<AccountStateNode>::create(Broker::OANDA);
  node->calculate();
}