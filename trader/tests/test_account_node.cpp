#include "AccountState.hpp"
#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include "nlohmann/json.hpp"
#include "trading_types.hpp"

using namespace std;
using namespace DataNodes;
using json = nlohmann::json;

TEST_F(DataNodeTest, TestAccountState) {
  auto node = DataNode<AccountStateNode>::create(Broker::FOREXCOM);
  node->logger->info(json(node->get_data()).dump());
  node = DataNode<AccountStateNode>::create(Broker::OANDA);
  node->calculate();
}