#pragma once
#include "DataNode.hpp"

template <typename A> class MovingAverage : public DataNode<MovingAverage<A>, double> {
  std::shared_ptr<DataNode<IDataNode, A>> _input_data;

public:
  MovingAverage(std::shared_ptr<DataNode<IDataNode, A>> node)
      : DataNode<MovingAverage<A>, double>(__func__, node) {
    _input_data = node;
  }

  void calculate() override {
    auto x = std::vector<double>({0, 1, 2, 3});
    this->set_data(x);
  }
};