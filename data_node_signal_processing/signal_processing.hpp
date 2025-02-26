#pragma once
#include "DataNode.hpp"

namespace DataNodes {

/*
A simple moving average for a single vector of values. The template value `InputType` needs to match
the DataNode type that is passed to the constructor. The SimpleMovingAverage returns a vector of
type `OutputType` (default `double`).

*/
template <typename InputType, typename OutputType = double>
class SimpleMovingAverage
    : public DataNode<SimpleMovingAverage<InputType, OutputType>, OutputType> {
  std::shared_ptr<DataNode<IDataNode, InputType>> _input_data;
  unsigned int _window_size;

public:
  SimpleMovingAverage(std::shared_ptr<DataNode<IDataNode, InputType>> node,
                      unsigned int window_size)
      : DataNode<SimpleMovingAverage<InputType, OutputType>, OutputType>(node, window_size),
        _window_size(window_size) {
    _input_data = this->add_upstream_node(node);
  }

  void calculate() override {
    std::vector<InputType> data = _input_data->get_data();
    std::vector<OutputType> sma = {};
    sma.reserve(data.size());
    OutputType total = OutputType();
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

/*
An exponential moving average for a single vector of values. The template value `InputType` needs
to match the DataNode type that is passed to the constructor. The ExponentialMovingAverage returns a
vector of type `OutputType` (default `double`).

*/
template <typename InputType, typename OutputType = double>
class ExponentialMovingAverage
    : public DataNode<ExponentialMovingAverage<InputType, OutputType>, OutputType> {
  std::shared_ptr<DataNode<IDataNode, InputType>> _input_data;
  double _factor;

public:
  ExponentialMovingAverage(std::shared_ptr<DataNode<IDataNode, InputType>> node, double factor)
      : DataNode<ExponentialMovingAverage<InputType, OutputType>, OutputType>(node, factor),
        _factor(factor) {
    _input_data = this->add_upstream_node(node);
  }

  void calculate() override {
    std::vector<InputType> data = _input_data->get_data();
    std::vector<OutputType> ema = {};
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