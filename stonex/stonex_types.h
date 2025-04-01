#pragma once
#include "trading_types.hpp"
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace StoneX {

struct Api2FALogonOnResponseDTO {
  int contactId;
  int contactCategoryId;
  std::string value;
};

inline void from_json(const json &j, Api2FALogonOnResponseDTO &resp) {
  j.at("contactId").get_to(resp.contactId);
  j.at("contactCategoryId").get_to(resp.contactCategoryId);
  j.at("value").get_to(resp.value);
}
inline void to_json(json &j, const Api2FALogonOnResponseDTO &o) {
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

inline void from_json(const json &j, ApiLogOnResponseDTO &resp) {

  j.at("session").get_to(resp.session);
  j.at("passwordChangeRequired").get_to(resp.passwordChangeRequired);
  j.at("allowedAccountOperator").get_to(resp.allowedAccountOperator);
  j.at("statusCode").get_to(resp.statusCode);
  j.at("is2FAEnabled") == nullptr ? resp.is2FAEnabled = false
                                  : j.at("is2FAEnabled").get_to(resp.is2FAEnabled);
  fill_from_json(resp.additional2FAMethods, "additional2FAMethods", j);
}
inline void to_json(json &j, const ApiLogOnResponseDTO &o) {
  j = json{{"session", o.session},
           {"passwordChangeRequired", o.passwordChangeRequired},
           {"allowedAccountOperator", o.allowedAccountOperator},
           {"statusCode", o.statusCode},
           {"is2FAEnabled", o.is2FAEnabled},
           {"additional2FAMethods", o.additional2FAMethods}};
}

struct LegalPartyDTO {
  int partyId;
  std::string personalEmailAddress;
  bool hasMultipleEmailAddresses;
  int legalPartyUniqueReference;
  bool isPiisProvided;
};
inline void from_json(const json &j, LegalPartyDTO &resp) {

  j.at("partyId").get_to(resp.partyId);
  j.at("personalEmailAddress").get_to(resp.personalEmailAddress);
  j.at("hasMultipleEmailAddresses").get_to(resp.hasMultipleEmailAddresses);
  j.at("legalPartyUniqueReference").get_to(resp.legalPartyUniqueReference);
  j.at("isPiisProvided").get_to(resp.isPiisProvided);
}
inline void to_json(json &j, const LegalPartyDTO &o) {
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
inline void from_json(const json &j, Timestamp &resp) {

  j.at("seconds").get_to(resp.seconds);
  j.at("nanos").get_to(resp.nanos);
}
inline void to_json(json &j, const Timestamp &o) {
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
inline void from_json(const json &j, ApiClientAccountDTO &resp) {
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
inline void to_json(json &j, const ApiClientAccountDTO &o) {
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
inline void from_json(const json &j, ApiAccountHolderDTO &resp) {

  j.at("partyId").get_to(resp.partyId);
  j.at("name").get_to(resp.name);
}
inline void to_json(json &j, const ApiAccountHolderDTO &o) {
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
inline void from_json(const json &j, ApiTradingAccountDTO &resp) {

  j.at("clientAccountId").get_to(resp.clientAccountId);
  j.at("tradingAccountId").get_to(resp.tradingAccountId);
  j.at("tradingAccountCode").get_to(resp.tradingAccountCode);
  j.at("tradingAccountStatus").get_to(resp.tradingAccountStatus);
  j.at("tradingAccountType").get_to(resp.tradingAccountType);
  j.at("tradingAccountName").get_to(resp.tradingAccountName);
}
inline void to_json(json &j, const ApiTradingAccountDTO &o) {
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
inline void from_json(const json &j, ApiAccountOperatorDTO &resp) {

  j.at("accountOperatorId").get_to(resp.accountOperatorId);
  j.at("is2FAEnabledAO").get_to(resp.is2FAEnabledAO);
  j.at("isNfaEnabledClient").get_to(resp.isNfaEnabledClient);
  j.at("isFifo").get_to(resp.isFifo);
  j.at("daysUntilExpiryForDemo").get_to(resp.daysUntilExpiryForDemo);
  j.at("isDMAClient").get_to(resp.isDMAClient);
  j.at("serviceOfferingId").get_to(resp.serviceOfferingId);
}
inline void to_json(json &j, const ApiAccountOperatorDTO &o) {
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
inline void from_json(const json &j, ApiClientAccountTokenDTO &resp) {

  j.at("clientAccountId").get_to(resp.clientAccountId);
  j.at("token").get_to(resp.token);
}
inline void to_json(json &j, const ApiClientAccountTokenDTO &o) {
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
inline void from_json(const json &j, ApiContractDTO &resp) {

  j.at("contractId").get_to(resp.contractId);
  j.at("isNIGO").get_to(resp.isNIGO);
  j.at("contractType").get_to(resp.contractType);
}
inline void to_json(json &j, const ApiContractDTO &o) {
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
inline void from_json(const json &j, ApiRestrictionDTO &resp) {

  j.at("clientAccountId").get_to(resp.clientAccountId);
  j.at("closeOnly").get_to(resp.closeOnly);
  j.at("acceptNewBusiness").get_to(resp.acceptNewBusiness);
}
inline void to_json(json &j, const ApiRestrictionDTO &o) {
  j = json{
      {"clientAccountId", o.clientAccountId},
      {"closeOnly", o.closeOnly},
      {"acceptNewBusiness", o.acceptNewBusiness},
  };
}

struct LogonUser {
  std::string logonUserName;
};
inline void from_json(const json &j, LogonUser &resp) {

  j.at("logonUserName").get_to(resp.logonUserName);
}
inline void to_json(json &j, const LogonUser &o) {
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
inline void from_json(const json &j, LinkedAccountResult &resp) {

  j.at("logonUser").get_to(resp.logonUser);
  fill_from_json(resp.legalParties, "legalParties", j);
  fill_from_json(resp.accountHolders, "accountHolders", j);
  fill_from_json(resp.clientAccounts, "clientAccounts", j);
  fill_from_json(resp.tradingAccounts, "tradingAccounts", j);
  fill_from_json(resp.accountOperators, "accountOperators", j);
  fill_from_json(resp.contracts, "contracts", j);
  fill_from_json(resp.restrictions, "restrictions", j);
}
inline void to_json(json &j, const LinkedAccountResult &o) {
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
inline void from_json(const json &j, CashEquity &resp) {

  j.at("clientAccountToken").get_to(resp.clientAccountToken);
}
inline void to_json(json &j, const CashEquity &o) {
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

inline void from_json(const json &j, AccountResult &resp) {

  fill_from_json(resp.legalParties, "legalParties", j);
  fill_from_json(resp.accountHolders, "accountHolders", j);
  fill_from_json(resp.clientAccounts, "clientAccounts", j);
  fill_from_json(resp.tradingAccounts, "tradingAccounts", j);
  fill_from_json(resp.accountOperators, "accountOperators", j);
  fill_from_json(resp.contracts, "contracts", j);
  fill_from_json(resp.restrictions, "restrictions", j);
  fill_from_json(resp.linkedClientAccounts, "linkedClientAccounts", j);
  fill_from_json(resp.cashEquity, "cashEquity", j);
}
inline void to_json(json &j, const AccountResult &o) {
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
inline void from_json(const json &j, ClientAccountMarginResponseDTO &resp) {

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
inline void to_json(json &j, const ClientAccountMarginResponseDTO &o) {
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

enum MarketTypeID {
  EQUITY = 1,
  INDEX,
  BOND,
  FX,
  COMMODITY,
  INTEREST_RATE,
  METALS,
  EQUITY_COMMON_STOCK,
  EQUITY_ADS,
  BINARY,
  SECTORS,
  FX_HEDGE
};

struct ApiMarketEodDTO {
  std::string marketEodUnit;
  int marketEodAmount;
};
inline void from_json(const json &j, ApiMarketEodDTO &resp) {

  fill_from_json(resp.marketEodUnit, "marketEodUnit", j);
  fill_from_json(resp.marketEodAmount, "marketEodAmount", j);
}
inline void to_json(json &j, const ApiMarketEodDTO &o) {
  j = json{
      {"marketEodUnit", o.marketEodUnit},
      {"marketEodAmount", o.marketEodAmount},
  };
}

struct ApiDateTimeOffsetDTO {
  std::string utcDateTime;
  int offsetMinutes;
};
inline void from_json(const json &j, ApiDateTimeOffsetDTO &resp) {

  fill_from_json(resp.utcDateTime, "utcDateTime", j);
  fill_from_json(resp.offsetMinutes, "offsetMinutes", j);
}
inline void to_json(json &j, const ApiDateTimeOffsetDTO &o) {
  j = json{
      {"utcDateTime", o.utcDateTime},
      {"offsetMinutes", o.offsetMinutes},
  };
}

struct ApiTradingDayTimesDTO {
  int dayOfWeek;
  ApiDateTimeOffsetDTO startTimeUtc;
  ApiDateTimeOffsetDTO endTimeUtc;
};
inline void from_json(const json &j, ApiTradingDayTimesDTO &resp) {

  fill_from_json(resp.dayOfWeek, "dayOfWeek", j);
  fill_from_json(resp.startTimeUtc, "startTimeUtc", j);
  fill_from_json(resp.endTimeUtc, "endTimeUtc", j);
}
inline void to_json(json &j, const ApiTradingDayTimesDTO &o) {
  j = json{
      {"dayOfWeek", o.dayOfWeek},
      {"startTimeUtc", o.startTimeUtc},
      {"endTimeUtc", o.endTimeUtc},
  };
}

struct ApiMarketSpreadDTO {
  std::string spreadTimeUtc;
  double spread;
  int spreadUnits;
};
inline void from_json(const json &j, ApiMarketSpreadDTO &resp) {

  fill_from_json(resp.spreadTimeUtc, "spreadTimeUtc", j);
  fill_from_json(resp.spread, "spread", j);
  fill_from_json(resp.spreadUnits, "spreadUnits", j);
}
inline void to_json(json &j, const ApiMarketSpreadDTO &o) {
  j = json{
      {"spreadTimeUtc", o.spreadTimeUtc},
      {"spread", o.spread},
      {"spreadUnits", o.spreadUnits},
  };
}

struct ApiStepMarginBandDTO {
  double lowerBound;
  double marginFactor;
};
inline void from_json(const json &j, ApiStepMarginBandDTO &resp) {

  fill_from_json(resp.lowerBound, "lowerBound", j);
  fill_from_json(resp.marginFactor, "marginFactor", j);
}
inline void to_json(json &j, const ApiStepMarginBandDTO &o) {
  j = json{
      {"lowerBound", o.lowerBound},
      {"marginFactor", o.marginFactor},
  };
}

struct ApiStepMarginDTO {
  bool eligibleForStepMargin;
  bool stepMarginConfigured;
  bool inheritedFromParentAccountOperator;
  std::vector<ApiStepMarginBandDTO> bands;
};
inline void from_json(const json &j, ApiStepMarginDTO &resp) {

  fill_from_json(resp.eligibleForStepMargin, "eligibleForStepMargin", j);
  fill_from_json(resp.stepMarginConfigured, "stepMarginConfigured", j);
  fill_from_json(resp.inheritedFromParentAccountOperator, "inheritedFromParentAccountOperator", j);
  fill_from_json(resp.bands, "bands", j);
}
inline void to_json(json &j, const ApiStepMarginDTO &o) {
  j = json{
      {"eligibleForStepMargin", o.eligibleForStepMargin},
      {"stepMarginConfigured", o.stepMarginConfigured},
      {"inheritedFromParentAccountOperator", o.inheritedFromParentAccountOperator},
      {"bands", o.bands},
  };
}

struct ApiFxFinancingDTO {
  std::string captureDateTime;
  double longPoints;
  double shortPoints;
  double longCharge;
  double shortCharge;
  double quantity;
  int chargeCurrencyId;
  int daysToRoll;
};
inline void from_json(const json &j, ApiFxFinancingDTO &resp) {

  fill_from_json(resp.captureDateTime, "captureDateTime", j);
  fill_from_json(resp.longPoints, "longPoints", j);
  fill_from_json(resp.shortPoints, "shortPoints", j);
  fill_from_json(resp.longCharge, "longCharge", j);
  fill_from_json(resp.shortCharge, "shortCharge", j);
  fill_from_json(resp.quantity, "quantity", j);
  fill_from_json(resp.chargeCurrencyId, "chargeCurrencyId", j);
  fill_from_json(resp.daysToRoll, "daysToRoll", j);
}
inline void to_json(json &j, const ApiFxFinancingDTO &o) {
  j = json{
      {"captureDateTime", o.captureDateTime},   {"longPoints", o.longPoints},
      {"shortPoints", o.shortPoints},           {"longCharge", o.longCharge},
      {"shortCharge", o.shortCharge},           {"quantity", o.quantity},
      {"chargeCurrencyId", o.chargeCurrencyId}, {"daysToRoll", o.daysToRoll},
  };
}

struct ApiKnockoutDTO {
  int pairedMarkets;
  int knockoutLevels;
  double knockoutIncrement;
  int knockoutIncrementUnits;
  double knockoutMinDistance;
  int knockoutMinDistanceUnits;
};
inline void from_json(const json &j, ApiKnockoutDTO &resp) {

  fill_from_json(resp.pairedMarkets, "pairedMarkets", j);
  fill_from_json(resp.knockoutLevels, "knockoutLevels", j);
  fill_from_json(resp.knockoutIncrement, "knockoutIncrement", j);
  fill_from_json(resp.knockoutIncrementUnits, "knockoutIncrementUnits", j);
  fill_from_json(resp.knockoutMinDistance, "knockoutMinDistance", j);
  fill_from_json(resp.knockoutMinDistanceUnits, "knockoutMinDistanceUnits", j);
}
inline void to_json(json &j, const ApiKnockoutDTO &o) {
  j = json{
      {"pairedMarkets", o.pairedMarkets},
      {"knockoutLevels", o.knockoutLevels},
      {"knockoutIncrement", o.knockoutIncrement},
      {"knockoutIncrementUnits", o.knockoutIncrementUnits},
      {"knockoutMinDistance", o.knockoutMinDistance},
      {"knockoutMinDistanceUnits", o.knockoutMinDistanceUnits},
  };
}

struct CorporateActionsDTO {
  int corporateActionId;
};
inline void from_json(const json &j, CorporateActionsDTO &resp) {

  fill_from_json(resp.corporateActionId, "corporateActionId", j);
}
inline void to_json(json &j, const CorporateActionsDTO &o) {
  j = json{
      {"corporateActionId", o.corporateActionId},
  };
}

enum MarketState {
  Tradable,
  TradableAndFast,
  Indicative,
  PhoneOnly,
  Close,
  Suspended,
  CloseOnly,
  LongOnly,
  ShortOnly
};

struct MarketPricesDTO {
  double bidPrice;
  double offerPrice;
  MarketState marketState;
};
inline void from_json(const json &j, MarketPricesDTO &resp) {

  fill_from_json(resp.bidPrice, "bidPrice", j);
  fill_from_json(resp.offerPrice, "offerPrice", j);
  fill_from_json(resp.marketState, "marketState", j);
}
inline void to_json(json &j, const MarketPricesDTO &o) {
  j = json{
      {"bidPrice", o.bidPrice},
      {"offerPrice", o.offerPrice},
      {"marketState", o.marketState},
  };
}

struct IdentifiersDTO {
  std::string identifierCode;
  std::string isin;
  std::string sedol;
};
inline void from_json(const json &j, IdentifiersDTO &resp) {

  fill_from_json(resp.identifierCode, "identifierCode", j);
  fill_from_json(resp.isin, "isin", j);
  fill_from_json(resp.sedol, "sedol", j);
}
inline void to_json(json &j, const IdentifiersDTO &o) {
  j = json{
      {"identifierCode", o.identifierCode},
      {"isin", o.isin},
      {"sedol", o.sedol},
  };
}

struct ApiMarketInformationDTO {
  int marketId;
  int chartMarketId;
  std::string name;
  int exchangeId;
  std::string exchangeName;
  double marginFactor;
  double minMarginFactor;
  int marginFactorUnits;
  double maxMarginFactor;
  double clientMarginFactor;
  double minDistance;
  int minDistanceUnits;
  double webMinSize;
  double maxSize;
  std::string marketSizesCurrencyCode;
  double maxLongSize;
  double maxShortSize;
  bool market24H;
  int priceDecimalPlaces;
  int defaultQuoteLength;
  bool tradeOnWeb;
  bool limitUp;
  bool limitDown;
  bool longPositionOnly;
  bool closeOnly;
  double incrementSize;
  std::vector<ApiMarketEodDTO> marketEod;
  double priceTolerance;
  int convertPriceToPipsMultiplier;
  int marketSettingsTypeId;
  std::string marketSettingsType;
  std::string mobileShortName;
  std::string centralClearingType;
  std::string centralClearingTypeDescription;
  int marketCurrencyId;
  double phoneMinSize;
  std::string dailyFinancingAppliedAtUtc;
  std::string nextMarketEodTimeUtc;
  std::string tradingStartTimeUtc;
  std::string tradingEndTimeUtc;
  std::vector<ApiTradingDayTimesDTO> marketPricingTimes;
  std::vector<ApiTradingDayTimesDTO> marketBreakTimes;
  std::vector<ApiMarketSpreadDTO> marketSpreads;
  double guaranteedOrderPremium;
  int guaranteedOrderPremiumUnits;
  double guaranteedOrderMinDistance;
  int guaranteedOrderMinDistanceUnits;
  double priceToleranceUnits;
  int marketTimeZoneOffsetMinutes;
  double quantityConversionFactor;
  int pointFactorDivisor;
  double betPer;
  MarketTypeID marketUnderlyingTypeId;
  std::string marketUnderlyingType;
  bool allowGuaranteedOrders;
  bool ordersAwareMargining;
  double ordersAwareMarginingMinimum;
  double commissionChargeMinimum;
  double commissionRate;
  int commissionRateUnits;
  std::string expiryUtc;
  ApiStepMarginDTO stepMargin;
  std::string futureRolloverUTC;
  bool allowRollover;
  int expiryBasisId;
  std::string expiryBasisText;
  int optionTypeId;
  std::string optionType;
  double strikePrice;
  int marketTypeId;
  std::string marketType;
  int weighting;
  ApiFxFinancingDTO fxFinancing;
  std::string underlyingRicCode;
  std::string newsUnderlyingOverrideType;
  std::string newsUnderlyingOverrideCode;
  double trailingStepConversionFactor;
  bool isDMA;
  bool isKnockout;
  ApiKnockoutDTO knockout;
  std::vector<CorporateActionsDTO> corporateActions;
  MarketPricesDTO prices;
  IdentifiersDTO identifiers;
  int marketUnderlyingId;
  std::string fullMarketName;
};
inline void from_json(const json &j, ApiMarketInformationDTO &resp) {

  fill_from_json(resp.marketId, "marketId", j);
  fill_from_json(resp.chartMarketId, "chartMarketId", j);
  fill_from_json(resp.name, "name", j);
  fill_from_json(resp.exchangeId, "exchangeId", j);
  fill_from_json(resp.exchangeName, "exchangeName", j);
  fill_from_json(resp.marginFactor, "marginFactor", j);
  fill_from_json(resp.minMarginFactor, "minMarginFactor", j);
  fill_from_json(resp.marginFactorUnits, "marginFactorUnits", j);
  fill_from_json(resp.maxMarginFactor, "maxMarginFactor", j);
  fill_from_json(resp.clientMarginFactor, "clientMarginFactor", j);
  fill_from_json(resp.minDistance, "minDistance", j);
  fill_from_json(resp.minDistanceUnits, "minDistanceUnits", j);
  fill_from_json(resp.webMinSize, "webMinSize", j);
  fill_from_json(resp.maxSize, "maxSize", j);
  fill_from_json(resp.marketSizesCurrencyCode, "marketSizesCurrencyCode", j);
  fill_from_json(resp.maxLongSize, "maxLongSize", j);
  fill_from_json(resp.maxShortSize, "maxShortSize", j);
  fill_from_json(resp.market24H, "market24H", j);
  fill_from_json(resp.priceDecimalPlaces, "priceDecimalPlaces", j);
  fill_from_json(resp.defaultQuoteLength, "defaultQuoteLength", j);
  fill_from_json(resp.tradeOnWeb, "tradeOnWeb", j);
  fill_from_json(resp.limitUp, "limitUp", j);
  fill_from_json(resp.limitDown, "limitDown", j);
  fill_from_json(resp.longPositionOnly, "longPositionOnly", j);
  fill_from_json(resp.closeOnly, "closeOnly", j);
  fill_from_json(resp.incrementSize, "incrementSize", j);
  fill_from_json(resp.marketEod, "marketEod", j);
  fill_from_json(resp.priceTolerance, "priceTolerance", j);
  fill_from_json(resp.convertPriceToPipsMultiplier, "convertPriceToPipsMultiplier", j);
  fill_from_json(resp.marketSettingsTypeId, "marketSettingsTypeId", j);
  fill_from_json(resp.marketSettingsType, "marketSettingsType", j);
  fill_from_json(resp.mobileShortName, "mobileShortName", j);
  fill_from_json(resp.centralClearingType, "centralClearingType", j);
  fill_from_json(resp.centralClearingTypeDescription, "centralClearingTypeDescription", j);
  fill_from_json(resp.marketCurrencyId, "marketCurrencyId", j);
  fill_from_json(resp.phoneMinSize, "phoneMinSize", j);
  fill_from_json(resp.dailyFinancingAppliedAtUtc, "dailyFinancingAppliedAtUtc", j);
  fill_from_json(resp.nextMarketEodTimeUtc, "nextMarketEodTimeUtc", j);
  fill_from_json(resp.tradingStartTimeUtc, "tradingStartTimeUtc", j);
  fill_from_json(resp.tradingEndTimeUtc, "tradingEndTimeUtc", j);
  fill_from_json(resp.marketPricingTimes, "marketPricingTimes", j);
  fill_from_json(resp.marketBreakTimes, "marketBreakTimes", j);
  fill_from_json(resp.marketSpreads, "marketSpreads", j);
  fill_from_json(resp.guaranteedOrderPremium, "guaranteedOrderPremium", j);
  fill_from_json(resp.guaranteedOrderPremiumUnits, "guaranteedOrderPremiumUnits", j);
  fill_from_json(resp.guaranteedOrderMinDistance, "guaranteedOrderMinDistance", j);
  fill_from_json(resp.guaranteedOrderMinDistanceUnits, "guaranteedOrderMinDistanceUnits", j);
  fill_from_json(resp.priceToleranceUnits, "priceToleranceUnits", j);
  fill_from_json(resp.marketTimeZoneOffsetMinutes, "marketTimeZoneOffsetMinutes", j);
  fill_from_json(resp.quantityConversionFactor, "quantityConversionFactor", j);
  fill_from_json(resp.pointFactorDivisor, "pointFactorDivisor", j);
  fill_from_json(resp.betPer, "betPer", j);
  fill_from_json(resp.marketUnderlyingTypeId, "marketUnderlyingTypeId", j);
  fill_from_json(resp.marketUnderlyingType, "marketUnderlyingType", j);
  fill_from_json(resp.allowGuaranteedOrders, "allowGuaranteedOrders", j);
  fill_from_json(resp.ordersAwareMargining, "ordersAwareMargining", j);
  fill_from_json(resp.ordersAwareMarginingMinimum, "ordersAwareMarginingMinimum", j);
  fill_from_json(resp.commissionChargeMinimum, "commissionChargeMinimum", j);
  fill_from_json(resp.commissionRate, "commissionRate", j);
  fill_from_json(resp.commissionRateUnits, "commissionRateUnits", j);
  fill_from_json(resp.expiryUtc, "expiryUtc", j);
  fill_from_json(resp.stepMargin, "stepMargin", j);
  fill_from_json(resp.futureRolloverUTC, "futureRolloverUTC", j);
  fill_from_json(resp.allowRollover, "allowRollover", j);
  fill_from_json(resp.expiryBasisId, "expiryBasisId", j);
  fill_from_json(resp.expiryBasisText, "expiryBasisText", j);
  fill_from_json(resp.optionTypeId, "optionTypeId", j);
  fill_from_json(resp.optionType, "optionType", j);
  fill_from_json(resp.strikePrice, "strikePrice", j);
  fill_from_json(resp.marketTypeId, "marketTypeId", j);
  fill_from_json(resp.marketType, "marketType", j);
  fill_from_json(resp.weighting, "weighting", j);
  fill_from_json(resp.fxFinancing, "fxFinancing", j);
  fill_from_json(resp.underlyingRicCode, "underlyingRicCode", j);
  fill_from_json(resp.newsUnderlyingOverrideType, "newsUnderlyingOverrideType", j);
  fill_from_json(resp.newsUnderlyingOverrideCode, "newsUnderlyingOverrideCode", j);
  // fill_from_json(resp.trailingStepConversionFactor, "trailingStepConversionFactor", j);
  fill_from_json(resp.isDMA, "isDMA", j);
  fill_from_json(resp.isKnockout, "isKnockout", j);
  fill_from_json(resp.knockout, "knockout", j);
  fill_from_json(resp.corporateActions, "corporateActions", j);
  fill_from_json(resp.prices, "prices", j);
  fill_from_json(resp.identifiers, "identifiers", j);
  fill_from_json(resp.marketUnderlyingId, "marketUnderlyingId", j);
  fill_from_json(resp.fullMarketName, "fullMarketName", j);
}
inline void to_json(json &j, const ApiMarketInformationDTO &o) {
  j = json{
      {"marketId", o.marketId},
      {"chartMarketId", o.chartMarketId},
      {"name", o.name},
      {"exchangeId", o.exchangeId},
      {"exchangeName", o.exchangeName},
      {"marginFactor", o.marginFactor},
      {"minMarginFactor", o.minMarginFactor},
      {"marginFactorUnits", o.marginFactorUnits},
      {"maxMarginFactor", o.maxMarginFactor},
      {"clientMarginFactor", o.clientMarginFactor},
      {"minDistance", o.minDistance},
      {"minDistanceUnits", o.minDistanceUnits},
      {"webMinSize", o.webMinSize},
      {"maxSize", o.maxSize},
      {"marketSizesCurrencyCode", o.marketSizesCurrencyCode},
      {"maxLongSize", o.maxLongSize},
      {"maxShortSize", o.maxShortSize},
      {"market24H", o.market24H},
      {"priceDecimalPlaces", o.priceDecimalPlaces},
      {"defaultQuoteLength", o.defaultQuoteLength},
      {"tradeOnWeb", o.tradeOnWeb},
      {"limitUp", o.limitUp},
      {"limitDown", o.limitDown},
      {"longPositionOnly", o.longPositionOnly},
      {"closeOnly", o.closeOnly},
      {"incrementSize", o.incrementSize},
      {"marketEod", o.marketEod},
      {"priceTolerance", o.priceTolerance},
      {"convertPriceToPipsMultiplier", o.convertPriceToPipsMultiplier},
      {"marketSettingsTypeId", o.marketSettingsTypeId},
      {"marketSettingsType", o.marketSettingsType},
      {"mobileShortName", o.mobileShortName},
      {"centralClearingType", o.centralClearingType},
      {"centralClearingTypeDescription", o.centralClearingTypeDescription},
      {"marketCurrencyId", o.marketCurrencyId},
      {"phoneMinSize", o.phoneMinSize},
      {"dailyFinancingAppliedAtUtc", o.dailyFinancingAppliedAtUtc},
      {"nextMarketEodTimeUtc", o.nextMarketEodTimeUtc},
      {"tradingStartTimeUtc", o.tradingStartTimeUtc},
      {"tradingEndTimeUtc", o.tradingEndTimeUtc},
      {"marketPricingTimes", o.marketPricingTimes},
      {"marketBreakTimes", o.marketBreakTimes},
      {"marketSpreads", o.marketSpreads},
      {"guaranteedOrderPremium", o.guaranteedOrderPremium},
      {"guaranteedOrderPremiumUnits", o.guaranteedOrderPremiumUnits},
      {"guaranteedOrderMinDistance", o.guaranteedOrderMinDistance},
      {"guaranteedOrderMinDistanceUnits", o.guaranteedOrderMinDistanceUnits},
      {"priceToleranceUnits", o.priceToleranceUnits},
      {"marketTimeZoneOffsetMinutes", o.marketTimeZoneOffsetMinutes},
      {"quantityConversionFactor", o.quantityConversionFactor},
      {"pointFactorDivisor", o.pointFactorDivisor},
      {"betPer", o.betPer},
      {"marketUnderlyingTypeId", o.marketUnderlyingTypeId},
      {"marketUnderlyingType", o.marketUnderlyingType},
      {"allowGuaranteedOrders", o.allowGuaranteedOrders},
      {"ordersAwareMargining", o.ordersAwareMargining},
      {"ordersAwareMarginingMinimum", o.ordersAwareMarginingMinimum},
      {"commissionChargeMinimum", o.commissionChargeMinimum},
      {"commissionRate", o.commissionRate},
      {"commissionRateUnits", o.commissionRateUnits},
      {"expiryUtc", o.expiryUtc},
      {"stepMargin", o.stepMargin},
      {"futureRolloverUTC", o.futureRolloverUTC},
      {"allowRollover", o.allowRollover},
      {"expiryBasisId", o.expiryBasisId},
      {"expiryBasisText", o.expiryBasisText},
      {"optionTypeId", o.optionTypeId},
      {"optionType", o.optionType},
      {"strikePrice", o.strikePrice},
      {"marketTypeId", o.marketTypeId},
      {"marketType", o.marketType},
      {"weighting", o.weighting},
      {"fxFinancing", o.fxFinancing},
      {"underlyingRicCode", o.underlyingRicCode},
      {"newsUnderlyingOverrideType", o.newsUnderlyingOverrideType},
      {"newsUnderlyingOverrideCode", o.newsUnderlyingOverrideCode},
      // {"trailingStepConversionFactor", o.trailingStepConversionFactor},
      {"isDMA", o.isDMA},
      {"isKnockout", o.isKnockout},
      {"knockout", o.knockout},
      {"corporateActions", o.corporateActions},
      {"prices", o.prices},
      {"identifiers", o.identifiers},
      {"marketUnderlyingId", o.marketUnderlyingId},
      {"fullMarketName", o.fullMarketName},
  };
}

struct ApiMarketTagDTO {
  int marketTagId;
  std::string name;
  int type;
  int weighting;
};
inline void from_json(const json &j, ApiMarketTagDTO &resp) {

  fill_from_json(resp.marketTagId, "marketTagId", j);
  fill_from_json(resp.name, "name", j);
  fill_from_json(resp.type, "type", j);
  fill_from_json(resp.weighting, "weighting", j);
}
inline void to_json(json &j, const ApiMarketTagDTO &o) {
  j = json{
      {"marketTagId", o.marketTagId},
      {"name", o.name},
      {"type", o.type},
      {"weighting", o.weighting},
  };
}

struct FullMarketInformationSearchWithTagsResponseDTO {
  std::vector<ApiMarketInformationDTO> marketInformation;
  std::vector<ApiMarketTagDTO> tags;
};
inline void from_json(const json &j, FullMarketInformationSearchWithTagsResponseDTO &resp) {

  fill_from_json(resp.marketInformation, "marketInformation", j);
  fill_from_json(resp.tags, "tags", j);
}
inline void to_json(json &j, const FullMarketInformationSearchWithTagsResponseDTO &o) {
  j = json{
      {"marketInformation", o.marketInformation},
      {"tags", o.tags},
  };
}

struct BarDate : public std::string {
  operator unsigned long() const {
    return std::stoul(std::string(this->begin() + 6, this->end() - 2));
  }
};

struct PriceBarDTO {
  BarDate barDate;
  double open;
  double close;
  double high;
  double low;
  double volume;
};
inline void from_json(const json &j, PriceBarDTO &resp) {

  fill_from_json(resp.barDate, "BarDate", j);
  fill_from_json(resp.open, "Open", j);
  fill_from_json(resp.close, "Close", j);
  fill_from_json(resp.high, "High", j);
  fill_from_json(resp.low, "Low", j);
}
inline void to_json(json &j, const PriceBarDTO &o) {
  j = json{
      {"BarDate", o.barDate}, {"Open", o.open}, {"Close", o.close},
      {"High", o.high},       {"Low", o.low},   {"Volume", o.volume},
  };
}

struct GetPriceBarResponseDTO {
  std::vector<PriceBarDTO> priceBars;
  PriceBarDTO partialPriceBar;
};
inline void from_json(const json &j, GetPriceBarResponseDTO &resp) {

  fill_from_json(resp.priceBars, "PriceBars", j);
  fill_from_json(resp.partialPriceBar, "PartialPriceBar", j);
}
inline void to_json(json &j, const GetPriceBarResponseDTO &o) {
  j = json{
      {"PriceBars", o.priceBars},
      {"PartialPriceBar", o.partialPriceBar},
  };
}

} // namespace StoneX