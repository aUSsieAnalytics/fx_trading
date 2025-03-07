#pragma once
#include "trading_types.hpp"
#include <array>
#include <iostream>

struct OpenForexOrder {
  std::string unique_id;
  ForexPair instrument;
  double quantity;
  double stop_loss;
  double take_profit;
  OrderDirection direction;
};

struct ForexPosition {
  ForexPair instrument;
  double quantity;
  OrderDirection direction;
};

struct AccountState {
  double cash;
  double equity;
  double margin;
  Currency currency;
};