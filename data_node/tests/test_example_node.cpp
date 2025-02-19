#include "DataNode.hpp"
#include <gtest/gtest.h>

using namespace std;
class ExampleNode : public DataNode<int, ExampleNode> {
  double _value1;
  int _value2;
  DataNodeShrPtr _math_node;

public:
  ExampleNode(double value1 = 0, int value2 = 0)
      : DataNode(__func__, value1, value2), _value1(value1), _value2(value2) {}
};

class ExampleNode2 : public DataNode<int, ExampleNode2>, public ExampleNode {
  double _value5;

public:
  ExampleNode2(double value5, DataNodeShrPtr math_node = make_shared<DataNode<int>>("DataNode"))
      : DataNode<int, ExampleNode2>(__func__, value5, math_node), ExampleNode(0.9, 7),
        _value5(value5) {}
};

TEST(DataTest, ExampleNodes) {
  auto example_one = DataNode<int, ExampleNode>::create(0, 1);
  auto example_two = DataNode<int, ExampleNode2>::create(3);
  string hash = example_one->get_hash();
  cout << hash;
}