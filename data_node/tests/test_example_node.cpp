#include "DataNode.hpp"
#include "data_node_test_utils.hpp"
#include <gtest/gtest.h>

using namespace std;
using namespace DataNodes;

class ExampleNode : public DataNode<ExampleNode> {
  double _value1;
  int _int_vector;

public:
  std::shared_ptr<OutputNode<double>> output_1;
  std::shared_ptr<OutputNode<int>> output_2;

  ExampleNode(double value1 = 0, int value2 = 0)
      : DataNode(value2), _value1(value1), _int_vector(value2) {
    output_1 = register_output_node<double>();
    output_2 = register_output_node<int>();
  }

  void calculate() override {
    auto x = std::vector<double>({_value1, static_cast<double>(_int_vector)});
    output_1->set_data(x);
    auto y = std::vector<int>({-1, _int_vector});
    output_2->set_data(y);
  };
};

class ExampleNode2 : public DataNode<ExampleNode2, int> {
  int _value5;
  std::shared_ptr<ExampleNode> _example_node;

public:
  ExampleNode2(double value5,
               std::shared_ptr<ExampleNode> math_node = DataNode<ExampleNode>::create())
      : DataNode<ExampleNode2, int>(value5, math_node), _value5(value5) {
    _example_node = math_node;
    add_upstream_node(math_node);
  }

  void calculate() override {
    auto x = _example_node->output_2->get_data();
    x.push_back(_value5);
    set_data(x);
  }
};

TEST_F(DataNodeTest, CallChildDataFirst) {
  IDataNode::clear_registry();
  int value = 3;
  auto example_one = DataNode<ExampleNode>::create(0, 1);
  auto example_two = DataNode<ExampleNode2>::create(value);
  ASSERT_EQ(example_one->output_1->get_data().size(), 2);
  ASSERT_EQ(example_two->get_data().size(), 3);
  ASSERT_EQ(example_two->get_data().at(example_two->get_data().size() - 1), value);
}

TEST_F(DataNodeTest, CallParentDataFirst) {
  IDataNode::clear_registry();
  int value = 3;
  auto example_one = DataNode<ExampleNode>::create(0, 1);
  auto example_two = DataNode<ExampleNode2>::create(value);
  example_one->output_1->calculate();
  ASSERT_EQ(example_one->output_1->get_data().size(), 2);
  ASSERT_EQ(example_two->get_data().size(), 3);
  ASSERT_EQ(example_two->get_data().at(example_two->get_data().size() - 1), value);
}