#include "DataNode.hpp"
#include "signal_processing.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

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

TEST(SignalProcessingTest, TestSimpleMovingAverage) {
  std::vector<double> double_vector = {1.0, 1.0, 1.0, 2.0, 2.0, 2.0};
  std::vector<int> int_vector = {1, 1, 1, 2, 2, 2};
  auto example_one = DataNode<ExampleNode>::create(double_vector, int_vector);
  auto sma_double = DataNode<SimpleMovingAverage<double>>::create(example_one->output_1, 3);
  auto double_result = sma_double->get_data();
  auto sma_int = DataNode<SimpleMovingAverage<int>>::create(example_one->output_2, 3);
  auto int_result = sma_int->get_data();

  ASSERT_EQ(double_result.at(0), 1.0);
  ASSERT_EQ(double_result.at(2), 1.0);
  ASSERT_EQ(double_result.at(5), 2.0);
  ASSERT_EQ(int_result.at(0), 1);
  ASSERT_EQ(int_result.at(2), 1);
  ASSERT_EQ(int_result.at(5), 2);
}