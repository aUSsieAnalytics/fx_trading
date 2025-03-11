#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

template <typename T>
void fill_vector_from_json(std::vector<T> &vector, const std::string &name, const json &j) {
  auto item = j.at(name);
  if (item == nullptr) {
    vector.clear();
    vector.reserve(0);
    return;
  }
  vector.reserve(item.size());
  for (auto &_j : item) {
    vector.push_back(_j.template get<T>());
  }
}

namespace StoneX {

struct Api2FALogonOnResponseDTO {};
void from_json(const json &j, Api2FALogonOnResponseDTO &resp) {
  if (j == nullptr)
    return;
}

struct ApiLogOnResponseDTO {
  std::string session;
  bool passwordChangeRequired;
  bool allowedAccountOperator;
  int statusCode;
  bool is2FAEnabled;
  std::string twoFAToken;
  std::vector<std::vector<Api2FALogonOnResponseDTO>> additional2FAMethods;
};

void from_json(const json &j, ApiLogOnResponseDTO &resp) {
  if (j == nullptr)
    return;

  j.at("session").get_to(resp.session);
  j.at("passwordChangeRequired").get_to(resp.passwordChangeRequired);
  j.at("allowedAccountOperator").get_to(resp.allowedAccountOperator);
  j.at("statusCode").get_to(resp.statusCode);
  j.at("is2FAEnabled") == nullptr ? resp.is2FAEnabled = ""
                                  : j.at("is2FAEnabled").get_to(resp.is2FAEnabled);
  fill_vector_from_json(resp.additional2FAMethods, "additional2FAMethods", j);
}

struct LegalPartyDTO {
  int partyId;
  std::string personalEmailAddress;
  bool hasMultipleEmailAddresses;
  int legalPartyUniqueReference;
  bool isPiisProvided;
};
void from_json(const json &j, LegalPartyDTO &resp) {
  if (j == nullptr)
    return;
  j.at("partyId").get_to(resp.partyId);
  j.at("personalEmailAddress").get_to(resp.personalEmailAddress);
  j.at("hasMultipleEmailAddresses").get_to(resp.hasMultipleEmailAddresses);
  j.at("legalPartyUniqueReference").get_to(resp.legalPartyUniqueReference);
  j.at("isPiisProvided").get_to(resp.isPiisProvided);
}

struct Timestamp {
  int seconds;
  int nanos;
};
void from_json(const json &j, Timestamp &resp) {
  if (j == nullptr)
    return;
  j.at("seconds").get_to(resp.seconds);
  j.at("nanos").get_to(resp.nanos);
}

struct ApiClientAccountDTO {
  int contractId;
  int clientAccountId;
  int cultureId;
  std::string clientAccountCurrency;
  int accountOperatorId;
  int clientTypeId;
  bool isMiFIDRegulator;
  Timestamp clientAccountCreationDate;
  bool isMetaTrader;
  int brandParentId;
  std::string accountGroupName;
};
void from_json(const json &j, ApiClientAccountDTO &resp) {
  j.at("contractId").get_to(resp.contractId);
  j.at("clientAccountId").get_to(resp.clientAccountId);
  j.at("cultureId").get_to(resp.cultureId);
  j.at("clientAccountCurrency").get_to(resp.clientAccountCurrency);
  j.at("accountOperatorId").get_to(resp.accountOperatorId);
  j.at("clientTypeId").get_to(resp.clientTypeId);
  j.at("isMiFIDRegulator").get_to(resp.isMiFIDRegulator);
  j.at("clientAccountCreationDate").get_to(resp.clientAccountCreationDate);
  j.at("isMetaTrader").get_to(resp.isMetaTrader);
  j.at("brandParentId").get_to(resp.brandParentId);
  j.at("accountGroupName").get_to(resp.accountGroupName);
}

struct ApiAccountHolderDTO {
  int partyId;
  std::string name;
};
void from_json(const json &j, ApiAccountHolderDTO &resp) {
  if (j == nullptr)
    return;
  j.at("partyId").get_to(resp.partyId);
  j.at("name").get_to(resp.name);
}

struct ApiTradingAccountDTO {
  int clientAccountId;
  int tradingAccountId;
  std::string tradingAccountCode;
  std::string tradingAccountStatus;
  std::string tradingAccountType;
  std::string tradingAccountName;
};
void from_json(const json &j, ApiTradingAccountDTO &resp) {
  if (j == nullptr)
    return;
  j.at("clientAccountId").get_to(resp.clientAccountId);
  j.at("tradingAccountId").get_to(resp.tradingAccountId);
  j.at("tradingAccountCode").get_to(resp.tradingAccountCode);
  j.at("tradingAccountStatus").get_to(resp.tradingAccountStatus);
  j.at("tradingAccountType").get_to(resp.tradingAccountType);
  j.at("tradingAccountName").get_to(resp.tradingAccountName);
}

struct ApiAccountOperatorDTO {
  int accountOperatorId;
  bool is2FAEnabledAO;
  bool isNfaEnabledClient;
  bool isFifo;
  int daysUntilExpiryForDemo;
  bool isDMAClient;
  int serviceOfferingId;
};
void from_json(const json &j, ApiAccountOperatorDTO &resp) {
  if (j == nullptr)
    return;
  j.at("accountOperatorId").get_to(resp.accountOperatorId);
  j.at("is2FAEnabledAO").get_to(resp.is2FAEnabledAO);
  j.at("isNfaEnabledClient").get_to(resp.isNfaEnabledClient);
  j.at("isFifo").get_to(resp.isFifo);
  j.at("daysUntilExpiryForDemo").get_to(resp.daysUntilExpiryForDemo);
  j.at("isDMAClient").get_to(resp.isDMAClient);
  j.at("serviceOfferingId").get_to(resp.serviceOfferingId);
}

struct ApiClientAccountTokenDTO {
  int clientAccountId;
  std::string token;
};
void from_json(const json &j, ApiClientAccountTokenDTO &resp) {
  if (j == nullptr)
    return;
  j.at("clientAccountId").get_to(resp.clientAccountId);
  j.at("token").get_to(resp.token);
}

struct ApiContractDTO {
  int contractId;
  bool isNIGO;
  int contractType;
};
void from_json(const json &j, ApiContractDTO &resp) {
  if (j == nullptr)
    return;
  j.at("contractId").get_to(resp.contractId);
  j.at("isNIGO").get_to(resp.isNIGO);
  j.at("contractType").get_to(resp.contractType);
}

struct ApiRestrictionDTO {
  int clientAccountId;
  bool closeOnly;
  bool acceptNewBusiness;
};
void from_json(const json &j, ApiRestrictionDTO &resp) {
  if (j == nullptr)
    return;
  j.at("clientAccountId").get_to(resp.clientAccountId);
  j.at("closeOnly").get_to(resp.closeOnly);
  j.at("acceptNewBusiness").get_to(resp.acceptNewBusiness);
}

struct LogonUser {
  std::string logonUserName;
};
void from_json(const json &j, LogonUser &resp) {
  if (j == nullptr)
    return;
  j.at("logonUserName").get_to(resp.logonUserName);
}

struct LinkedAccountResult {
  LogonUser logonUser;
  std::vector<LegalPartyDTO> legalParties;
  std::vector<ApiAccountHolderDTO> accountHolders;
  std::vector<ApiClientAccountDTO> clientAccounts;
  std::vector<ApiTradingAccountDTO> tradingAccounts;
  std::vector<ApiAccountOperatorDTO> accountOperators;
  std::vector<ApiContractDTO> contracts;
  std::vector<ApiRestrictionDTO> restrictions;
};
void from_json(const json &j, LinkedAccountResult &resp) {
  if (j == nullptr)
    return;
  j.at("logonUser").get_to(resp.logonUser);
  fill_vector_from_json(resp.legalParties, "legalParties", j);
  fill_vector_from_json(resp.accountHolders, "accountHolders", j);
  fill_vector_from_json(resp.clientAccounts, "clientAccounts", j);
  fill_vector_from_json(resp.tradingAccounts, "tradingAccounts", j);
  fill_vector_from_json(resp.accountOperators, "accountOperators", j);
  fill_vector_from_json(resp.contracts, "contracts", j);
  fill_vector_from_json(resp.restrictions, "restrictions", j);
}

struct CashEquity {
  ApiClientAccountTokenDTO clientAccountToken;
};
void from_json(const json &j, CashEquity &resp) {
  if (j == nullptr)
    return;
  j.at("clientAccountToken").get_to(resp.clientAccountToken);
}

struct AccountResult {
  std::vector<LegalPartyDTO> legalParties;
  std::vector<ApiAccountHolderDTO> accountHolders;
  std::vector<ApiClientAccountDTO> clientAccounts;
  std::vector<ApiTradingAccountDTO> tradingAccounts;
  std::vector<ApiAccountOperatorDTO> accountOperators;
  std::vector<ApiContractDTO> contracts;
  std::vector<ApiRestrictionDTO> restrictions;
  std::vector<LinkedAccountResult> linkedClientAccounts;
  CashEquity cashEquity;
};

void from_json(const json &j, AccountResult &resp) {
  if (j == nullptr)
    return;
  fill_vector_from_json(resp.legalParties, "legalParties", j);
  fill_vector_from_json(resp.accountHolders, "accountHolders", j);
  fill_vector_from_json(resp.clientAccounts, "clientAccounts", j);
  fill_vector_from_json(resp.tradingAccounts, "tradingAccounts", j);
  fill_vector_from_json(resp.accountOperators, "accountOperators", j);
  fill_vector_from_json(resp.contracts, "contracts", j);
  fill_vector_from_json(resp.restrictions, "restrictions", j);
  fill_vector_from_json(resp.linkedClientAccounts, "linkedClientAccounts", j);
  j.at("cashEquity").get_to(resp.cashEquity);
}
} // namespace StoneX