#pragma once
#include "cpr/cpr.h"
#include "stonex_types.h"
#include "trading_types.hpp"
#include <nlohmann/json.hpp>
#include <unordered_map>

using json = nlohmann::json;

namespace StoneX {

const inline std::string base_url = "https://ciapi.cityindex.com/v2";
const inline std::string trading_url = "https://ciapi.cityindex.com/TradingAPI";

inline std::shared_ptr<std::string> base_url_ptr = std::make_shared<std::string>(base_url);
inline std::shared_ptr<std::string> trading_url_ptr = std::make_shared<std::string>(trading_url);

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

inline std::shared_ptr<cpr::Session> session = std::make_shared<cpr::Session>();

AccountResult get_account_info() {
  if (!AccountCredentials::authorized) {
    if (!authorize_stonex()) {
      throw std::runtime_error("Could not authorize session.");
    }
  }
  session->SetUrl(cpr::Url{*base_url_ptr + "/UserAccount/ClientAndTradingAccount"});
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
  session->SetHeader(header);
  session->SetBody(body);
  session->SetUrl(cpr::Url{*base_url_ptr + "/Session"});
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
  session->SetUrl(cpr::Url{*base_url_ptr + "/margin/clientAccountMargin"});
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
  session->SetUrl(cpr::Url{*base_url_ptr + "/market/fullSearchWithTags"});
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
  session->SetUrl(cpr::Url{*trading_url_ptr + "/market/" + market_id + "/barhistory"});
  cpr::Parameters params;
  params.Add({"clientAccountId", std::to_string(AccountCredentials::account_id)});
  params.Add({"span", std::to_string(span)});
  params.Add({"interval", std::to_string(period_unit)});
  params.Add({"PriceType", std::to_string(price_type)});
  params.Add({"PriceBars", std::to_string(number_of_bars)});
  session->SetParameters(params);
  cpr::Response resp = StoneX::session->Get();
  GetPriceBarResponseDTO candles = json::parse(resp.text).template get<GetPriceBarResponseDTO>();
  return candles;
}

GetPriceBarResponseDTO get_price_bars_between(ForexPair pair, long utc_from, long utc_to, int span,
                                              CandlePeriodUnit period_unit,
                                              PriceType price_type = PriceType::MID) {
  std::string market_id = std::to_string(get_market_info(pair).marketId);
  session->SetUrl(cpr::Url{*trading_url_ptr + "/market/" + market_id + "/barhistorybetween"});
  cpr::Parameters params;
  params.Add({"clientAccountId", std::to_string(AccountCredentials::account_id)});
  params.Add({"span", std::to_string(span)});
  params.Add({"interval", std::to_string(period_unit)});
  params.Add({"PriceType", std::to_string(price_type)});
  params.Add({"fromTimestampUTC", std::to_string(utc_from)});
  params.Add({"toTimestampUTC", std::to_string(utc_to)});
  params.Add({"maxResults", "4000"});

  session->SetParameters(params);
  cpr::Response resp = StoneX::session->Get();
  GetPriceBarResponseDTO candles = json::parse(resp.text).template get<GetPriceBarResponseDTO>();
  return candles;
}

} // namespace StoneX