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
        _input_data(node), _window_size(window_size) {}

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
        _input_data(node), _factor(factor) {}

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

/*
Check if two vectors of values cross each other. The template values `InputType1`,`InputType2` need
to match the DataNode types that are passed to the constructor..

*/
template <typename InputType1, typename InputType2>
class CrossOver : public DataNode<CrossOver<InputType1, InputType2>, bool> {
  std::shared_ptr<DataNode<IDataNode, InputType1>> _input_data1;
  std::shared_ptr<DataNode<IDataNode, InputType2>> _input_data2;

public:
  CrossOver(std::shared_ptr<DataNode<IDataNode, InputType1>> node1,
            std::shared_ptr<DataNode<IDataNode, InputType2>> node2)
      : DataNode<CrossOver<InputType1, InputType2>, bool>(node1, node2), _input_data1(node1),
        _input_data2(node2) {}

  void calculate() override {
    std::vector<InputType1> data1 = _input_data1->get_data();
    std::vector<InputType2> data2 = _input_data2->get_data();
    std::vector<bool> crossovers = std::vector<bool>(std::max(data1.size(), data2.size()), false);

    if (data1.size() == 0 || data2.size() == 0) {
      this->set_data(crossovers);
      return;
    }
    unsigned int i = 1;
    bool data1_crossing_up = false;
    if (i < data1.size() && i < data2.size()) {
      data1_crossing_up = data1[0] < data2[0];
    }

    while (i < data1.size() && i < data2.size()) {
      if ((data1[i] > data2[i] && data2[i - 1] > data1[i - 1] && data1_crossing_up) ||
          (data1[i] < data2[i] && data2[i - 1] < data1[i - 1] && !data1_crossing_up)) {
        crossovers[i] = true;
        data1_crossing_up = !data1_crossing_up;
      }
      i++;
    }

    this->set_data(crossovers);
  }
};

} // namespace DataNodes