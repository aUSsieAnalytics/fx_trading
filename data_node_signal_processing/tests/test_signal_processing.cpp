#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include "signal_processing.hpp"
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