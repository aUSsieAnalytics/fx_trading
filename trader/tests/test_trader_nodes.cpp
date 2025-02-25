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

  auto example_one = DataNode<DataNode<IDataNode, CandleStick>, CandleStick>::create();
  example_one->set_data(candlesticks);
  auto high_prices = DataNode<CandleStickSplitter>::create(example_one, CandleStickPrice::HIGH);
  auto result = high_prices->get_data();
  EXPECT_NEAR(result.at(0), 2.0, 1e-4);
  EXPECT_NEAR(result.at(1), 3.0, 1e-4);
  EXPECT_NEAR(result.at(2), 4.0, 1e-4);
  EXPECT_NEAR(result.at(3), 5.0, 1e-4);
}