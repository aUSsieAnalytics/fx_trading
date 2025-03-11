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

struct Api2FALogonOnResponseDTO {
  int contactId;
  int contactCategoryId;
  std::string value;
};
void from_json(const json &j, Api2FALogonOnResponseDTO &resp) {
  if (j == nullptr)
    return;
  j.at("contactId").get_to(resp.contactId);
  j.at("contactCategoryId").get_to(resp.contactCategoryId);
  j.at("value").get_to(resp.value);
}
void to_json(json &j, const Api2FALogonOnResponseDTO &o) {
  j = json{
      {"contactId", o.contactId},
      {"contactCategoryId", o.contactCategoryId},
      {"value", o.value},
  };
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
void to_json(json &j, const ApiLogOnResponseDTO &o) {
  j = json{
      {"session", o.session},
      {"passwordChangeRequired", o.passwordChangeRequired},
      {"allowedAccountOperator", o.allowedAccountOperator},
      {"statusCode", o.statusCode},
      {"is2FAEnabled", o.is2FAEnabled},
  };
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
void to_json(json &j, const LegalPartyDTO &o) {
  j = json{
      {"partyId", o.partyId},
      {"personalEmailAddress", o.personalEmailAddress},
      {"hasMultipleEmailAddresses", o.hasMultipleEmailAddresses},
      {"legalPartyUniqueReference", o.legalPartyUniqueReference},
      {"isPiisProvided", o.isPiisProvided},
  };
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
void to_json(json &j, const Timestamp &o) {
  j = json{
      {"seconds", o.seconds},
      {"nanos", o.nanos},
  };
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
void to_json(json &j, const ApiClientAccountDTO &o) {
  j = json{
      {"contractId", o.contractId},
      {"clientAccountId", o.clientAccountId},
      {"cultureId", o.cultureId},
      {"clientAccountCurrency", o.clientAccountCurrency},
      {"accountOperatorId", o.accountOperatorId},
      {"clientTypeId", o.clientTypeId},
      {"isMiFIDRegulator", o.isMiFIDRegulator},
      {"clientAccountCreationDate", o.clientAccountCreationDate},
      {"isMetaTrader", o.isMetaTrader},
      {"brandParentId", o.brandParentId},
      {"accountGroupName", o.accountGroupName},
  };
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
void to_json(json &j, const ApiAccountHolderDTO &o) {
  j = json{
      {"partyId", o.partyId},
      {"name", o.name},
  };
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
void to_json(json &j, const ApiTradingAccountDTO &o) {
  j = json{
      {"clientAccountId", o.clientAccountId},
      {"tradingAccountId", o.tradingAccountId},
      {"tradingAccountCode", o.tradingAccountCode},
      {"tradingAccountStatus", o.tradingAccountStatus},
      {"tradingAccountType", o.tradingAccountType},
      {"tradingAccountName", o.tradingAccountName},
  };
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
void to_json(json &j, const ApiAccountOperatorDTO &o) {
  j = json{
      {"accountOperatorId", o.accountOperatorId},           {"is2FAEnabledAO", o.is2FAEnabledAO},
      {"isNfaEnabledClient", o.isNfaEnabledClient},         {"isFifo", o.isFifo},
      {"daysUntilExpiryForDemo", o.daysUntilExpiryForDemo}, {"isDMAClient", o.isDMAClient},
      {"serviceOfferingId", o.serviceOfferingId},
  };
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
void to_json(json &j, const ApiClientAccountTokenDTO &o) {
  j = json{
      {"clientAccountId", o.clientAccountId},
      {"token", o.token},
  };
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
void to_json(json &j, const ApiContractDTO &o) {
  j = json{
      {"contractId", o.contractId},
      {"isNIGO", o.isNIGO},
      {"contractType", o.contractType},
  };
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
void to_json(json &j, const ApiRestrictionDTO &o) {
  j = json{
      {"clientAccountId", o.clientAccountId},
      {"closeOnly", o.closeOnly},
      {"acceptNewBusiness", o.acceptNewBusiness},
  };
}

struct LogonUser {
  std::string logonUserName;
};
void from_json(const json &j, LogonUser &resp) {
  if (j == nullptr)
    return;
  j.at("logonUserName").get_to(resp.logonUserName);
}
void to_json(json &j, const LogonUser &o) {
  j = json{
      {"logonUserName", o.logonUserName},
  };
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
void to_json(json &j, const LinkedAccountResult &o) {
  j = json{
      {"logonUser", o.logonUser},
      {"legalParties", o.legalParties},
      {"accountHolders", o.accountHolders},
      {"clientAccounts", o.clientAccounts},
      {"tradingAccounts", o.tradingAccounts},
      {"accountOperators", o.accountOperators},
      {"contracts", o.contracts},
      {"restrictions", o.restrictions},
  };
}

struct CashEquity {
  ApiClientAccountTokenDTO clientAccountToken;
};
void from_json(const json &j, CashEquity &resp) {
  if (j == nullptr)
    return;
  j.at("clientAccountToken").get_to(resp.clientAccountToken);
}
void to_json(json &j, const CashEquity &o) {
  j = json{
      {"clientAccountToken", o.clientAccountToken},
  };
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
void to_json(json &j, const AccountResult &o) {
  j = json{
      {"legalParties", o.legalParties},
      {"accountHolders", o.accountHolders},
      {"clientAccounts", o.clientAccounts},
      {"tradingAccounts", o.tradingAccounts},
      {"accountOperators", o.accountOperators},
      {"contracts", o.contracts},
      {"restrictions", o.restrictions},
      {"linkedClientAccounts", o.linkedClientAccounts},
      {"cashEquity", o.cashEquity},
  };
}

struct ClientAccountMarginResponseDTO {
  double cash;
  double margin;
  double marginIndicator;
  double netEquity;
  double openTradeEquity;
  double tradableFunds;
  double pendingFunds;
  double tradingResource;
  double totalMarginRequirement;
  int currencyId;
  std::string currencyIsoCode;
};
void from_json(const json &j, ClientAccountMarginResponseDTO &resp) {
  if (j == nullptr)
    return;
  j.at("cash").get_to(resp.cash);
  j.at("margin").get_to(resp.margin);
  j.at("marginIndicator").get_to(resp.marginIndicator);
  j.at("openTradeEquity").get_to(resp.openTradeEquity);
  j.at("tradableFunds").get_to(resp.tradableFunds);
  j.at("pendingFunds").get_to(resp.pendingFunds);
  j.at("tradingResource").get_to(resp.tradingResource);
  j.at("totalMarginRequirement").get_to(resp.totalMarginRequirement);
  j.at("currencyIsoCode").get_to(resp.currencyIsoCode);
}
void to_json(json &j, const ClientAccountMarginResponseDTO &o) {
  j = json{
      {"cash", o.cash},
      {"margin", o.margin},
      {"marginIndicator", o.marginIndicator},
      {"openTradeEquity", o.openTradeEquity},
      {"tradableFunds", o.tradableFunds},
      {"pendingFunds", o.pendingFunds},
      {"tradingResource", o.tradingResource},
      {"totalMarginRequirement", o.totalMarginRequirement},
      {"currencyIsoCode", o.currencyIsoCode},
  };
}

} // namespace StoneX