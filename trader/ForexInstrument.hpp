#include "DataNode.hpp"
#include "trading_types.hpp"

namespace DataNodes {

class ForexInstrument : public DataNode<ForexInstrument, CandleStick> {
  ForexPair _pair;

public:
  ForexInstrument(ForexPair pair) : DataNode(pair), _pair(pair) {}
};

} // namespace DataNodes