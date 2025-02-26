#include "CandleStickSplitter.hpp"
#include "CrossOver.hpp"
#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include "trading_types.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace DataNodes;

class ExampleNode : public DataNode<ExampleNode, double> {
  std::vector<double> _double_vector;
  std::vector<int> _int_vector;

public:
  std::shared_ptr<DataNode<IDataNode, double>> output_1;
  std::shared_ptr<DataNode<IDataNode, int>> output_2;

  ExampleNode(std::vector<double> double_vector, std::vector<int> int_vector)
      : DataNode(double_vector, int_vector), _double_vector(double_vector),
        _int_vector(int_vector) {
    output_1 = register_output_node<double>();
    output_2 = register_output_node<int>();
  }

  void calculate() override {
    set_data(_double_vector);
    output_1->set_data(_double_vector);
    output_2->set_data(_int_vector);
  };
};

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

TEST_F(DataNodeTest, TestCrossOvers) {
  std::vector<double> double_vector = {1.0, 1.0, 1.1, 2.1, 2.1, 3.0, 4.0};
  std::vector<int> int_vector = {0, 1, 1, 2, 2, 4, 3};
  auto example_one = DataNode<ExampleNode>::create(double_vector, int_vector);
  auto crossover_node =
      DataNode<CrossOver<double, int>>::create(example_one->output_1, example_one->output_2);
  auto crossovers = crossover_node->get_data();

  ASSERT_EQ(crossovers.at(0), false);
  ASSERT_EQ(crossovers.at(1), false);
  ASSERT_EQ(crossovers.at(2), false);
  ASSERT_EQ(crossovers.at(3), false);
  ASSERT_EQ(crossovers.at(4), false);
  ASSERT_EQ(crossovers.at(5), true);
  ASSERT_EQ(crossovers.at(6), true);

  double_vector.clear();
  example_one = DataNode<ExampleNode>::create(double_vector, int_vector);
  auto crossover_node2 =
      DataNode<CrossOver<double, int>>::create(example_one->output_1, example_one->output_2);
  crossovers = crossover_node2->get_data();
  ASSERT_EQ(crossovers.at(0), false);
  ASSERT_EQ(crossovers.at(1), false);
  ASSERT_EQ(crossovers.at(2), false);
  ASSERT_EQ(crossovers.at(3), false);
  ASSERT_EQ(crossovers.at(4), false);
  ASSERT_EQ(crossovers.at(5), false);
  ASSERT_EQ(crossovers.at(6), false);

  std::vector<CandleStick> candlesticks1 = {};
  std::vector<CandleStick> candlesticks2 = {};

  for (int i = 0; i < 5; i++) {
    candlesticks1.emplace_back(CandleStick(i, i, i, i));
    candlesticks2.emplace_back(CandleStick(i, i, i, i));
  }

  candlesticks1.at(2).open = 0;
  candlesticks2.at(2).open = 1;
  candlesticks1.at(2).close = 4;
  candlesticks2.at(2).close = 3;

  auto candle_stick_node1 = DataNode<DataNode<IDataNode, CandleStick>, CandleStick>::create("1");
  candle_stick_node1->set_data(candlesticks1);
  auto candle_stick_node2 = DataNode<DataNode<IDataNode, CandleStick>, CandleStick>::create("2");
  candle_stick_node2->set_data(candlesticks2);

  auto candle_stick_crossover =
      DataNode<CrossOver<CandleStick, CandleStick>>::create(candle_stick_node1, candle_stick_node2);
  auto crossovers_candles = candle_stick_crossover->get_data();
  ASSERT_EQ(crossovers_candles.at(0), false);
  ASSERT_EQ(crossovers_candles.at(1), false);
  ASSERT_EQ(crossovers_candles.at(2), true);
  ASSERT_EQ(crossovers_candles.at(3), false);
  ASSERT_EQ(crossovers_candles.at(4), false);
}