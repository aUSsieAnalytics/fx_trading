#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include "signal_processing.hpp"
#include "trading_types.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace DataNodes;

class ExampleNode : public DataNode<ExampleNode, void> {
  std::vector<double> _double_vector;
  std::vector<int> _int_vector;

public:
  std::shared_ptr<OutputNode<std::vector<double>>> output_1;
  std::shared_ptr<OutputNode<std::vector<int>>> output_2;

  ExampleNode(std::vector<double> double_vector, std::vector<int> int_vector)
      : DataNode(double_vector, int_vector), _double_vector(double_vector),
        _int_vector(int_vector) {
    output_1 = register_output_node<std::vector<double>>();
    output_2 = register_output_node<std::vector<int>>();
  }

  void calculate() override {
    output_1->set_data(_double_vector);
    output_2->set_data(_int_vector);
  };
};

TEST_F(DataNodeTest, TestSimpleMovingAverage) {
  std::vector<double> double_vector = {1.0, 1.0, 1.0, 2.0, 2.0, 2.0};
  std::vector<int> int_vector = {1, 1, 1, 2, 2, 2};
  auto example_one = DataNode<ExampleNode>::create(double_vector, int_vector);
  auto sma_double = DataNode<SimpleMovingAverage<double>>::create(example_one->output_1, 3);
  auto double_result = sma_double->get_data();
  auto sma_int = DataNode<SimpleMovingAverage<int>>::create(example_one->output_2, 3);
  auto int_result = sma_int->get_data();

  EXPECT_NEAR(double_result.at(0), 1.0, 1e-4);
  EXPECT_NEAR(double_result.at(2), 1.0, 1e-4);
  EXPECT_NEAR(double_result.at(3), 1.3333, 1e-4);
  EXPECT_NEAR(double_result.at(5), 2.0, 1e-4);
  EXPECT_NEAR(int_result.at(0), 1.0, 1e-4);
  EXPECT_NEAR(int_result.at(2), 1.0, 1e-4);
  EXPECT_NEAR(int_result.at(3), 1.33333, 1e-4);
  EXPECT_NEAR(int_result.at(5), 2.0, 1e-4);
}

TEST_F(DataNodeTest, TestCandleStickSMA) {
  std::vector<CandleStick> candlesticks = {};
  for (int i = 0; i < 5; i++) {
    candlesticks.emplace_back(CandleStick(i, i + 1, i + 2, i + 3));
  }

  auto example_one = DataNode<OutputNode<std::vector<CandleStick>>>::create();
  example_one->logger->serialize();
  example_one->set_data(candlesticks);
  auto sma = DataNode<SimpleMovingAverage<CandleStick, CandleStick>>::create(example_one, 3);
  auto result = sma->get_data();
  EXPECT_NEAR(result.at(0).open, 0.0, 1e-4);
  EXPECT_NEAR(result.at(0).close, 1.0, 1e-4);
  EXPECT_NEAR(result.at(4).open, 3.0, 1e-4);
  EXPECT_NEAR(result.at(4).close, 4.0, 1e-4);
}

TEST_F(DataNodeTest, TestExponentialMovingAverage) {
  std::vector<double> double_vector = {1.0, 1.0, 1.0, 2.0, 2.0, 2.0};
  std::vector<int> int_vector = {1, 1, 1, 2, 2, 2};
  auto example_one = DataNode<ExampleNode>::create(double_vector, int_vector);
  auto ema_double = DataNode<ExponentialMovingAverage<double>>::create(example_one->output_1, 0.5);
  auto double_result = ema_double->get_data();
  auto ema_int = DataNode<ExponentialMovingAverage<int>>::create(example_one->output_2, 0.5);
  auto int_result = ema_int->get_data();

  EXPECT_NEAR(double_result.at(0), 1.0, 1e-4);
  EXPECT_NEAR(double_result.at(2), 1.0, 1e-4);
  EXPECT_NEAR(double_result.at(3), 1.5, 1e-4);
  EXPECT_NEAR(double_result.at(5), 1.875, 1e-4);
  EXPECT_NEAR(int_result.at(0), 1.0, 1e-4);
  EXPECT_NEAR(int_result.at(2), 1.0, 1e-4);
  EXPECT_NEAR(int_result.at(3), 1.5, 1e-4);
  EXPECT_NEAR(int_result.at(5), 1.875, 1e-4);
}

TEST_F(DataNodeTest, TestCandleStickEMA) {
  std::vector<CandleStick> candlesticks = {};
  for (int i = 0; i < 5; i++) {
    candlesticks.emplace_back(CandleStick(i, i + 1, i + 2, i + 3));
  }

  auto example_one = DataNode<OutputNode<std::vector<CandleStick>>>::create();
  example_one->set_data(candlesticks);
  auto ema = DataNode<ExponentialMovingAverage<CandleStick, CandleStick>>::create(example_one, 0.5);
  auto result = ema->get_data();
  EXPECT_NEAR(result.at(0).open, 0.0, 1e-4);
  EXPECT_NEAR(result.at(0).close, 1.0, 1e-4);
  EXPECT_NEAR(result.at(4).open, 3.0625, 1e-4);
  EXPECT_NEAR(result.at(4).close, 4.0625, 1e-4);
}
