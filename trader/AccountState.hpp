#include "DataNode.hpp"
#include "trading_types.hpp"


namespace DataNodes {

class AccountStateNode : public DataNode<AccountStateNode, AccountState> {
  Broker _broker;
  std::string _username;
  std::string _appkey;
  std::string _password;

public:
  AccountStateNode(Broker broker): DataNode(broker), _broker(broker) {
    
  }
};

} // namespace DataNodes
