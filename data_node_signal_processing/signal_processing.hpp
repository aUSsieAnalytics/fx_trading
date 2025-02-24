#pragma once
#include "DataNode.hpp"

namespace DataNodes {

template <typename A> class SimpleMovingAverage : public DataNode<SimpleMovingAverage<A>, double> {
  std::shared_ptr<DataNode<IDataNode, A>> _input_data;
  unsigned int _window_size;

public:
  SimpleMovingAverage(std::shared_ptr<DataNode<IDataNode, A>> node, unsigned int window_size)
      : DataNode<SimpleMovingAverage<A>, double>(node, window_size), _input_data(node),
        _window_size(window_size) {}

  void calculate() override {
    std::vector<A> data = _input_data->get_data();
    std::vector<double> sma = {};
    sma.reserve(data.size());
    double total = 0;
    for (unsigned int i = 0; i < data.size(); i++) {
      total += data[i];
      if (i < _window_size) {
        sma.push_back(total / (i + 1));
        continue;
      }
      total -= data[i - _window_size];
      sma.push_back(total / _window_size);
    }
    this->set_data(sma);
  }
};
} // namespace DataNodes