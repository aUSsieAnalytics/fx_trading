#pragma once
#include "DataNode.hpp"
#include "stonex.h"
#include "trading_types.hpp"

namespace DataNodes {

class ForexInstrumentNode : public DataNode<ForexInstrumentNode, void> {
  ForexPair _pair;
  Granularity _granularity;
  PriceType _price;
  Broker _broker;

public:
  std::shared_ptr<OutputNode<std::vector<CandleStick>>> candle_sticks;
  std::shared_ptr<OutputNode<std::vector<unsigned long>>> utc_time_ms;

  ForexInstrumentNode(ForexPair pair, Granularity granularity, PriceType price = PriceType::MID,
                      Broker broker = Broker::FOREXCOM)
      : DataNode(pair, granularity), _pair(pair), _granularity(granularity), _price(price),
        _broker(broker) {
    candle_sticks = register_output_node<std::vector<CandleStick>>();
    utc_time_ms = register_output_node<std::vector<unsigned long>>("utc_time_ms");
  }

  void calculate() override {
    // only doing forexcom for now. Will NOT include latest partial candle
    auto interval_and_span = StoneX::granularity_to_interval_and_span.at(_granularity);
    auto candles = StoneX::get_latest_price_bars(_pair, 200, interval_and_span.second,
                                                 interval_and_span.first, _price);
    std::vector<CandleStick> candle_buffer;
    std::vector<unsigned long> time;
    candle_buffer.reserve(candles.priceBars.size());
    candle_buffer.resize(candles.priceBars.size());
    time.reserve(candles.priceBars.size());
    time.resize(candles.priceBars.size());
    int i = 0;
    for (auto const c : candles.priceBars) {
      candle_buffer[i].close = c.close;
      candle_buffer[i].high = c.high;
      candle_buffer[i].low = c.low;
      candle_buffer[i].open = c.open;
      time[i] = c.barDate;
      i++;
    }
    candle_sticks->set_data(candle_buffer);
    utc_time_ms->set_data(time);
  };
};

} // namespace DataNodes