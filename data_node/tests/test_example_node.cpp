#include "DataNode.hpp"
#include <gtest/gtest.h>

using namespace std;
class ExampleNode : virtual public DataNode<int> {
  double _value1;
  int _value2;

public:
  ExampleNode(double value1, int value2)
      : _value1(), _value2(), DataNode(__func__, value1, value2) {}
};

class ExampleNode2 : public ExampleNode {
  double _value5;

public:
  ExampleNode2(double value5) : DataNode(__func__, value5), ExampleNode(0.9, 7) {}
};

TEST(DataTest, ExampleNodes) {
  DataNode<int> example_one = ExampleNode(1, 2);
  DataNode<int> example_two = ExampleNode2(3);
  string hash = example_one.get_hash();
  cout << hash;
}