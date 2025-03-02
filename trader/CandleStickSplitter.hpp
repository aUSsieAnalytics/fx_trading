#pragma once

#include "DataNode.hpp"
#include "trading_types.hpp"

namespace DataNodes {

class CandleStickSplitter : public DataNode<CandleStickSplitter, double> {
  CandleStickPrice _price;
  std::shared_ptr<OutputNode<CandleStick>> _node;

public:
  CandleStickSplitter(std::shared_ptr<OutputNode<CandleStick>> node,
                      CandleStickPrice const price)
      : DataNode<CandleStickSplitter, double>(node, price), _price(price) {
    _node = this->add_upstream_node(node);
  }

  void calculate() override {
    auto data = _node->get_data();
    std::vector<double> parsed_data = {};
    parsed_data.reserve(data.size());

    switch (_price) {
    case CandleStickPrice::OPEN:
      for (auto &candle : data) {
        parsed_data.push_back(candle.open);
      }
      break;
    case CandleStickPrice::CLOSE:
      for (auto &candle : data) {
        parsed_data.push_back(candle.close);
      }
      break;
    case CandleStickPrice::HIGH:
      for (auto &candle : data) {
        parsed_data.push_back(candle.high);
      }
      break;
    case CandleStickPrice::LOW:
      for (auto &candle : data) {
        parsed_data.push_back(candle.low);
      }
      break;
    }
    set_data(parsed_data);
  }
};

} // namespace DataNodes