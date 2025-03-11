#include "DataNode.hpp"
#include "cpr/cpr.h"
#include "orders.hpp"
#include "stonex.h"
#include <nlohmann/json.hpp>

namespace DataNodes {

class AccountStateNode : public DataNode<AccountStateNode, AccountState> {
  Broker _broker;

public:
  AccountStateNode(Broker broker) : DataNode(broker), _broker(broker) {}

  void calculate() {
    auto local_logger = this->logger;
    auto account_status = StoneX::get_account_status();
    local_logger->info("number of account holders: " +
                       std::to_string(account_status.accountHolders.size()));
  }
};

} // namespace DataNodes
