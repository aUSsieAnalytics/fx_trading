#include "DataNode.hpp"
#include "trading_types.hpp"

namespace DataNodes {

class ForexInstrument : public DataNode<ForexInstrument, void> {
  ForexPair _pair;
  Granularity _granularity;

public:
  std::shared_ptr<OutputNode<std::vector<CandleStick>>> candle_sticks_bid;
  std::shared_ptr<OutputNode<std::vector<CandleStick>>> candle_sticks_mid;
  std::shared_ptr<OutputNode<std::vector<CandleStick>>> candle_sticks_ask;
  std::shared_ptr<OutputNode<std::vector<unsigned long>>> utc_time_ms;

  ForexInstrument(ForexPair pair, Granularity granularity)
      : DataNode(pair, granularity), _pair(pair), _granularity(granularity) {
    candle_sticks_bid = register_output_node<std::vector<CandleStick>>("bid");
    candle_sticks_mid = register_output_node<std::vector<CandleStick>>("mid");
    candle_sticks_ask = register_output_node<std::vector<CandleStick>>("ask");
    utc_time_ms = register_output_node<std::vector<unsigned long>>("utc_time_ms");
  }
};

} // namespace DataNodes