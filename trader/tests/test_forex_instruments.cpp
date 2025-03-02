#include "DataNode.hpp"
#include "ForexInstrument.hpp"
#include "data_node_test_utils.hpp"
#include "trading_types.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace DataNodes;

TEST_F(DataNodeTest, TestForexInstrument) {
  std::vector<CandleStick> candlesticks = {};

  for (int i = 0; i < 5; i++) {
    candlesticks.emplace_back(CandleStick(i, i, i, i));
  }

  auto eur_usd = DataNode<ForexInstrument>::create(ForexPair::EURUSD);
  eur_usd->candle_sticks_bid->set_data(candlesticks);
}