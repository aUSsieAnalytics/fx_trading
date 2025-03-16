#pragma once
#include "cpr/cpr.h"
#include "stonex_types.h"
#include "trading_types.hpp"
#include <nlohmann/json.hpp>
#include <unordered_map>

using json = nlohmann::json;

namespace StoneX {

const inline std::string_view base_url = "https://ciapi.cityindex.com/v2";
const inline std::string_view trading_url = "https://ciapi.cityindex.com/TradingAPI";
std::unordered_map<std::string, ApiMarketInformationDTO> markets;

struct AccountCredentials {
  static inline std::string username = "";
  static inline std::string appkey = "";
  static inline std::string password = "";
  static inline bool authorized = false;
  static inline bool initialized = false;
  static inline int account_id = 0;
};

bool authorize_stonex() {
  if (AccountCredentials::authorized) {
    return true;
  }
  if (auto appkey = std::getenv("STONEX_APPKEY")) {
    AccountCredentials::appkey = appkey;
  } else {
    return false;
  }
  if (auto user = std::getenv("STONEX_USER")) {
    AccountCredentials::username = user;
  } else {
    return false;
  }
  if (auto pass = std::getenv("STONEX_PASS")) {
    AccountCredentials::password = pass;
  } else {
    return false;
  }
  AccountCredentials::authorized = true;
  return true;
}

std::shared_ptr<cpr::Session> session;

AccountResult get_account_info() {
  if (!AccountCredentials::authorized) {
    if (!authorize_stonex()) {
      throw std::runtime_error("Could not initialize session.");
    }
  }
  session->SetUrl(cpr::Url{std::string(base_url) + "/UserAccount/ClientAndTradingAccount"});
  cpr::Response resp = StoneX::session->Get();
  return json::parse(resp.text).template get<AccountResult>();
}

bool initialize_session() {
  if (!AccountCredentials::authorized) {
    if (!authorize_stonex()) {
      return false;
    }
  }
  auto body = cpr::Body(json({{"UserName", AccountCredentials::username},
                              {"Password", AccountCredentials::password},
                              {"AppKey", AccountCredentials::appkey}})
                            .dump());
  auto header =
      cpr::Header{{"Content-Type", "application/json"}, {"UserName", AccountCredentials::username}};
  session = std::make_shared<cpr::Session>();
  session->SetHeader(header);
  session->SetBody(body);
  session->SetUrl(cpr::Url{std::string(base_url) + "/Session"});
  cpr::Response resp = session->Post();
  if (resp.status_code != 200) {
    return false;
  }
  ApiLogOnResponseDTO sess_resp = json::parse(resp.text).template get<ApiLogOnResponseDTO>();
  std::string sess_id = sess_resp.session;
  header["Session"] = sess_id;
  session->SetHeader(header);
  auto account_info = get_account_info();
  AccountCredentials::account_id = account_info.tradingAccounts.at(0).clientAccountId;
  AccountCredentials::initialized = true;
  return true;
}

ClientAccountMarginResponseDTO get_account_margin() {
  if (AccountCredentials::account_id == 0) {
    if (!initialize_session()) {
      throw std::runtime_error("Could not initialize the session.");
    }
  }
  session->SetUrl(cpr::Url{std::string(base_url) + "/margin/clientAccountMargin"});
  session->SetParameters(
      cpr::Parameters{{"clientAccountId", std::to_string(AccountCredentials::account_id)}});
  cpr::Response resp = StoneX::session->Get();
  return json::parse(resp.text).template get<ClientAccountMarginResponseDTO>();
}

ApiMarketInformationDTO get_market_info(ForexPair pair) {
  std::string pair_as_string = std::to_string(pair);
  std::string search_string = pair_as_string;
  if (markets.contains(pair_as_string)) {
    return markets[pair_as_string];
  }

  if (AccountCredentials::account_id == 0) {
    if (!initialize_session()) {
      throw std::runtime_error("Could not initialize the session.");
    }
  }

  search_string.insert(3, "/");
  session->SetUrl(cpr::Url{std::string(base_url) + "/market/fullSearchWithTags"});
  session->SetParameters(
      cpr::Parameters{{"clientAccountId", std::to_string(AccountCredentials::account_id)},
                      {"query", search_string},
                      {"searchByMarketName", "true"},
                      {"maxResults", "50"}});
  cpr::Response resp = StoneX::session->Get();
  FullMarketInformationSearchWithTagsResponseDTO found_markets =
      json::parse(resp.text).template get<FullMarketInformationSearchWithTagsResponseDTO>();
  markets[pair_as_string] = found_markets.marketInformation[0];
  return markets[pair_as_string];
}

GetPriceBarResponseDTO get_latest_price_bars(ForexPair pair, int number_of_bars, int span,
                                             CandlePeriodUnit period_unit,
                                             PriceType price_type = PriceType::MID) {
  std::string market_id = std::to_string(get_market_info(pair).marketId);
  session->SetUrl(cpr::Url{std::string(trading_url) + "/market/" + market_id + "/barhistory"});
  session->SetParameters(
      cpr::Parameters{{"clientAccountId", std::to_string(AccountCredentials::account_id)},
                      {"span", std::to_string(span)},
                      {"interval", std::to_string(period_unit)},
                      {"PriceType", std::to_string(price_type)},
                      {"PriceBars", std::to_string(number_of_bars)}});
  cpr::Response resp = StoneX::session->Get();
  GetPriceBarResponseDTO candles = json::parse(resp.text).template get<GetPriceBarResponseDTO>();
  return candles;
}

} // namespace StoneX