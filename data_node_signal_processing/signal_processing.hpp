#pragma once
#include "DataNode.hpp"

namespace DataNodes {

/*
A simple moving average for a single vector of values. The template value (A) needs to match the
DataNode type that is passed to the constructor. The SimpleMovingAverage always returns a vector
of type double.

*/
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

template <typename A>
class ExponentialMovingAverage : public DataNode<ExponentialMovingAverage<A>, double> {
  std::shared_ptr<DataNode<IDataNode, A>> _input_data;
  double _factor;

public:
  ExponentialMovingAverage(std::shared_ptr<DataNode<IDataNode, A>> node, double factor)
      : DataNode<ExponentialMovingAverage<A>, double>(node, factor), _input_data(node),
        _factor(factor) {}

  void calculate() override {
    std::vector<A> data = _input_data->get_data();
    std::vector<double> ema = {};
    ema.reserve(data.size());
    if (data.size() >= 1) {
      ema.push_back(data[0]);
    }
    for (unsigned int i = 1; i < data.size(); i++) {
      ema.push_back((data[i] * _factor) + (ema[i - 1] * (1 - _factor)));
    }
    this->set_data(ema);
  }
};

} // namespace DataNodes