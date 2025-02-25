#include "DataNode.hpp"
#include "signal_processing.hpp"
#include "trading_types.hpp"
#include <iostream>

using namespace std;
using namespace DataNodes;

// class ExampleNode : public DataNode<ExampleNode, double> {
//   std::vector<double> _double_vector;
//   std::vector<int> _int_vector;

// public:
//   std::shared_ptr<DataNode<IDataNode, double>> output_1;
//   std::shared_ptr<DataNode<IDataNode, int>> output_2;

//   ExampleNode(std::vector<double> double_vector, std::vector<int> int_vector)
//       : DataNode(double_vector, int_vector), _double_vector(double_vector),
//         _int_vector(int_vector) {
//     output_1 = register_output_node<double>();
//     output_2 = register_output_node<int>();
//   }

//   void calculate() override {
//     set_data(_double_vector);
//     output_1->set_data(_double_vector);
//     output_2->set_data(_int_vector);
//   };
// };

int main() {

  std::vector<CandleStick> candlesticks = {};
  for (int i = 0; i < 5; i++) {
    candlesticks.emplace_back(CandleStick(i, i + 1, i + 2, i + 3));
  }

  auto example_one = DataNode<DataNode<IDataNode, CandleStick>, CandleStick>::create();
  example_one->set_data(candlesticks);
  // auto ema = DataNode<ExponentialMovingAverage<CandleStick, CandleStick>>::create(example_one,
  // 0.5); auto result = ema->get_data();
  cout << "done";
}