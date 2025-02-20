#include "DataNode.hpp"
#include <gtest/gtest.h>

using namespace std;

class ExampleNode : public DataNode<ExampleNode, double> {
  double _value1;
  int _value2;
  DataNodeShrPtr _math_node;

public:
  ExampleNode(double value1 = 0, int value2 = 0)
      : DataNode(__func__, value1, value2), _value1(value1), _value2(value2) {}

  std::shared_ptr<std::vector<double>> calculate() {
    return std::shared_ptr<std::vector<double>>(
        new std::vector<double>({_value1, static_cast<double>(_value2)}));
  };
};

class ExampleNode2 : public DataNode<ExampleNode2, int> {
  int _value5;

public:
  ExampleNode2(double value5, DataNodeShrPtr math_node = DataNode<>::create("DataNode"))
      : DataNode<ExampleNode2, int>(__func__, value5, math_node), _value5(value5) {}

  std::shared_ptr<std::vector<int>> calculate() {
    return std::shared_ptr<std::vector<int>>(new std::vector<int>({0, _value5}));
  }
};

TEST(DataTest, ExampleNodes) {
  auto example_one = DataNode<ExampleNode>::create(0, 1);
  auto example_two = DataNode<ExampleNode2>::create(3);
  string hash = example_one->get_hash();
  ASSERT_EQ(example_one->get_data()->size(), 2);
  ASSERT_EQ(example_two->get_data()->size(), 2);
}