#include "DataNode.hpp"
#include "ForexInstrument.hpp"
#include "stonex.h"
#include "trading_types.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace DataNodes;
using json = nlohmann::json;

TEST(LiveNodeTests, TestForexInstrument) {
  auto eur_usd = DataNode<ForexInstrumentNode>::create(ForexPair::EURUSD, Granularity::M1);
  std::cout << eur_usd->candle_sticks->get_data().size() << "\n";
}