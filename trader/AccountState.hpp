#include "DataNode.hpp"
#include "trading_types.hpp"

namespace DataNodes {

// class AccountState : public DataNode<AccountState, void> {
//   ForexPair _pair;
//   Granularity _granularity;

// public:
//   std::shared_ptr<OutputNode<CandleStick>> candle_sticks_bid;
//   std::shared_ptr<OutputNode<CandleStick>> candle_sticks_mid;
//   std::shared_ptr<OutputNode<CandleStick>> candle_sticks_ask;
//   std::shared_ptr<OutputNode<unsigned long>> utc_time_ms;

//   ForexInstrument(ForexPair pair, Granularity granularity)
//       : DataNode(pair, granularity), _pair(pair), _granularity(granularity) {
//     candle_sticks_bid = register_output_node<CandleStick>("bid");
//     candle_sticks_mid = register_output_node<CandleStick>("mid");
//     candle_sticks_ask = register_output_node<CandleStick>("ask");
//     utc_time_ms = register_output_node<unsigned long>("time_ms");
//   }
// };

} // namespace DataNodes