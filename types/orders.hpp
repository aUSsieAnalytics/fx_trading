#pragma once
#include "trading_types.hpp"
#include <array>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
void from_json(const json &j, AccountState &resp) {
  if (j == nullptr)
    return;
  j.at("cash").get_to(resp.cash);
  j.at("equity").get_to(resp.equity);
  j.at("margin").get_to(resp.margin);
  j.at("currency").get_to(resp.currency);
}
void to_json(json &j, const AccountState &o) {
  j = json{
      {"cash", o.cash},
      {"equity", o.equity},
      {"margin", o.margin},
      {"currency", o.currency},
  };
}