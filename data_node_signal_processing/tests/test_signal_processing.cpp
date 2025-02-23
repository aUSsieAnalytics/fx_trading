#include "DataNode.hpp"
#include "signal_processing.hpp"
#include <gtest/gtest.h>

using namespace std;

class ExampleNode : public DataNode<ExampleNode, double> {
  double _value1;
  int _value2;

public:
  std::shared_ptr<DataNode<IDataNode, double>> output_1;
  std::shared_ptr<DataNode<IDataNode, int>> output_2;

  ExampleNode(double value1 = 0, int value2 = 0)
      : DataNode(__func__, value2), _value1(value1), _value2(value2) {
    output_1 = register_output_node<double>("output_1");
    output_2 = register_output_node<int>();
  }

  void calculate() override {
    auto x = std::vector<double>({0, static_cast<double>(_value2), 1, 1, 1});
    set_data(x);
    output_1->set_data(x);
    auto y = std::vector<int>({-1, _value2, 3, 3, 3});
    output_2->set_data(y);
  };
};

TEST(SignalProcessingTest, TestMovingAverage) {
  auto example_one = DataNode<ExampleNode>::create(0, 1);
  auto sma_double = DataNode<MovingAverage<double>>::create(example_one->output_1);
  sma_double->get_data();
  auto sma_int = DataNode<MovingAverage<int>>::create(example_one->output_2);
  sma_int->get_data();
}