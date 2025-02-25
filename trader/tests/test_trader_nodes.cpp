#include "CandleStickSplitter.hpp"
#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include "trading_types.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace DataNodes;

TEST_F(DataNodeTest, TestCandleStickSplitter) {
  std::vector<CandleStick> candlesticks = {};
  for (int i = 0; i < 5; i++) {
    candlesticks.emplace_back(CandleStick(i, i + 1, i + 2, i + 3));
  }

  auto candle_stick_node = DataNode<DataNode<IDataNode, CandleStick>, CandleStick>::create();
  candle_stick_node->set_data(candlesticks);

  auto high_prices =
      DataNode<CandleStickSplitter>::create(candle_stick_node, CandleStickPrice::HIGH);
  auto low_prices = DataNode<CandleStickSplitter>::create(candle_stick_node, CandleStickPrice::LOW);
  auto open_prices =
      DataNode<CandleStickSplitter>::create(candle_stick_node, CandleStickPrice::OPEN);
  auto close_prices =
      DataNode<CandleStickSplitter>::create(candle_stick_node, CandleStickPrice::CLOSE);

  auto highs = high_prices->get_data();
  auto lows = low_prices->get_data();
  auto opens = open_prices->get_data();
  auto closes = close_prices->get_data();

  EXPECT_NEAR(highs.at(0), 2.0, 1e-4);
  EXPECT_NEAR(highs.at(1), 3.0, 1e-4);
  EXPECT_NEAR(highs.at(2), 4.0, 1e-4);
  EXPECT_NEAR(highs.at(3), 5.0, 1e-4);

  EXPECT_NEAR(lows.at(0), 3.0, 1e-4);
  EXPECT_NEAR(lows.at(1), 4.0, 1e-4);
  EXPECT_NEAR(lows.at(2), 5.0, 1e-4);
  EXPECT_NEAR(lows.at(3), 6.0, 1e-4);

  EXPECT_NEAR(opens.at(0), 0.0, 1e-4);
  EXPECT_NEAR(opens.at(1), 1.0, 1e-4);
  EXPECT_NEAR(opens.at(2), 2.0, 1e-4);
  EXPECT_NEAR(opens.at(3), 3.0, 1e-4);

  EXPECT_NEAR(closes.at(0), 1.0, 1e-4);
  EXPECT_NEAR(closes.at(1), 2.0, 1e-4);
  EXPECT_NEAR(closes.at(2), 3.0, 1e-4);
  EXPECT_NEAR(closes.at(3), 4.0, 1e-4);
}