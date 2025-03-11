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
    StoneX::ClientAccountMarginResponseDTO account_margin_stonex;

    switch (this->_broker) {
    case Broker::FOREXCOM:
      account_margin_stonex = StoneX::get_account_margin();
      this->set_data({account_margin_stonex.cash, account_margin_stonex.netEquity,
                      account_margin_stonex.margin, Currency::EUR});
      break;
    default:
      this->logger->warn("Broker of type '" + std::to_string(this->_broker) + "' not supported.");
    }
  }
};

} // namespace DataNodes
