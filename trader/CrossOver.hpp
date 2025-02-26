#pragma once

#include "DataNode.hpp"
#include "trading_types.hpp"

namespace DataNodes {
/*
Check if two vectors of values cross each other. The template values `InputType1`,`InputType2` need
to match the DataNode types that are passed to the constructor..

*/
template <typename InputType1, typename InputType2>
class CrossOver : public DataNode<CrossOver<InputType1, InputType2>, bool> {
  std::shared_ptr<DataNode<IDataNode, InputType1>> _input_data1;
  std::shared_ptr<DataNode<IDataNode, InputType2>> _input_data2;

  template <typename A, typename B>
  bool crossover_check(const std::vector<A> &data1, const std::vector<B> &data2,
                       const unsigned int i, const bool data1_crossing_up) {
    return (data1[i] > data2[i] && data2[i - 1] > data1[i - 1] && data1_crossing_up) ||
           (data1[i] < data2[i] && data2[i - 1] < data1[i - 1] && !data1_crossing_up);
  }

  bool crossover_check(const std::vector<CandleStick> &data1, const std::vector<CandleStick> &data2,
                       const unsigned int i, const bool data1_crossing_up) {
    return (data1[i].close > data2[i].close && data2[i].open > data1[i].open) ||
           (data1[i].close < data2[i].close && data2[i].open < data1[i].open);
  }

  template <typename A, typename B>
  bool initial_direction(const std::vector<A> &data1, const std::vector<B> &data2) {
    return data1[0] < data2[0];
  }

  bool initial_direction(const std::vector<CandleStick> &data1,
                         const std::vector<CandleStick> &data2) {
    return false;
  }

public:
  CrossOver(std::shared_ptr<DataNode<IDataNode, InputType1>> node1,
            std::shared_ptr<DataNode<IDataNode, InputType2>> node2)
      : DataNode<CrossOver<InputType1, InputType2>, bool>(node1, node2) {
    _input_data1 = this->add_upstream_node(node1);
    _input_data2 = this->add_upstream_node(node2);
  }

  void calculate() override {
    std::vector<InputType1> data1 = _input_data1->get_data();
    std::vector<InputType2> data2 = _input_data2->get_data();
    std::vector<bool> crossovers = std::vector<bool>(std::max(data1.size(), data2.size()), false);

    if (data1.size() == 0 || data2.size() == 0) {
      this->set_data(crossovers);
      return;
    }

    bool data1_crossing_up = initial_direction(data1, data2);

    for (unsigned int i = 1; i < data1.size() && i < data2.size(); i++) {
      if (crossover_check(data1, data2, i, data1_crossing_up)) {
        crossovers[i] = true;
        data1_crossing_up = !data1_crossing_up;
      }
    }

    this->set_data(crossovers);
  }
};
} // namespace DataNodes