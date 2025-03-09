#include "DataNode.hpp"
#include "cpr/cpr.h"
#include "orders.hpp"

namespace DataNodes {

class AccountStateNode : public DataNode<AccountStateNode, AccountState> {
  Broker _broker;
  std::string _username;
  std::string _appkey;
  std::string _password;

public:
  AccountStateNode(Broker broker) : DataNode(broker), _broker(broker) {}

  void calculate() {
    cpr::Response r = cpr::Get(cpr::Url{"https://httpbin.org/get"});
    this->logger->info(r.text);
  }
};

} // namespace DataNodes
