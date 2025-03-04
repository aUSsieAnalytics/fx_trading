#include "DataNode.hpp"
#include "trading_types.hpp"

namespace DataNodes {

class AccountStateNode : public DataNode<AccountStateNode, AccountState> {

public:
  AccountStateNode() : DataNode(pair, granularity) {}
};

} // namespace DataNodes