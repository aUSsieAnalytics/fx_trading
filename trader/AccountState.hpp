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
    auto account_margin = StoneX::get_account_margin();
    this->set_data(
        {account_margin.cash, account_margin.netEquity, account_margin.margin, Currency::EUR});
  }
};

} // namespace DataNodes
