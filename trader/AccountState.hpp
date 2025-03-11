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

  void calculate() { auto local_logger = this->logger; }
};

} // namespace DataNodes
