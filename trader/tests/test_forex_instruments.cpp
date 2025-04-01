#include "DataNode.hpp"
#include "ForexInstrument.hpp"
#include "stonex_node_mock.hpp"
#include "trading_types.hpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace DataNodes;

TEST_F(StoneXDataNodeTest, TestForexInstrument) {
  StoneX::AccountCredentials::authorized = true;
  StoneX::AccountCredentials::initialized = true;
  StoneX::AccountCredentials::account_id = 1234;

  StoneX::GetPriceBarResponseDTO bars;

  bars.partialPriceBar = {{"/Date(5010000)"}, 1, 2, 3, 4, 5};
  for (int i = 0; i < 5; i++) {
    bars.priceBars.push_back(
        StoneX::PriceBarDTO{{"/Date(500000" + std::to_string(i) + "0)/"}, 1, 2, 3, 4.0 + i, 5.0});
  }
  StoneX::ApiMarketInformationDTO info;
  info.marketId = 2020;
  StoneX::FullMarketInformationSearchWithTagsResponseDTO resp;
  resp.marketInformation.push_back(info);
  StoneX::markets["EURUSD"] = info;

  svr->Get("/market/2020/barhistory", [&](const httplib::Request &req, httplib::Response &res) {
    res.set_content(json(bars).dump(), "application/json");
  });

  auto eur_usd = DataNode<ForexInstrumentNode>::create(ForexPair::EURUSD, Granularity::M1,
                                                       PriceType::BID, Broker::FOREXCOM);
  auto candles = eur_usd->candle_sticks->get_data();
  EXPECT_EQ(candles.size(), 5);
  EXPECT_EQ(candles[3].low, 7);
}