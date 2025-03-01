#include "DataNode.hpp"
#include "trading_types.hpp"

namespace DataNodes {

class ForexInstrument : public DataNode<ForexInstrument, void> {
  ForexPair _pair;

public:
  std::shared_ptr<OutputNode<CandleStick>> candle_sticks;
  std::shared_ptr<OutputNode<unsigned long>> utc_time_ms;

  ForexInstrument(ForexPair pair) : DataNode(pair), _pair(pair) {
    candle_sticks = register_output_node<CandleStick>();
    utc_time_ms = register_output_node<unsigned long>();
  }
};

} // namespace DataNodes