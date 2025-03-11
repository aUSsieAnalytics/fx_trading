#pragma once
#include "cpr/cpr.h"
#include "stonex_types.h"
#include <nlohmann/json.hpp>
#include <unordered_map>

using json = nlohmann::json;

namespace StoneX {

const inline std::string_view base_url = "https://ciapi.cityindex.com/v2";

struct AccountCredentials {
  static inline std::string username = "";
  static inline std::string appkey = "";
  static inline std::string password = "";
  static inline bool authorized = false;
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
  return true;
}

AccountResult get_account_status() {
  session->SetUrl(cpr::Url{std::string(base_url) + "/UserAccount/ClientAndTradingAccount"});
  cpr::Response resp = StoneX::session->Get();
  return json::parse(resp.text).template get<AccountResult>();
}

} // namespace StoneX