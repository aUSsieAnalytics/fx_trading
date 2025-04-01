#include "stonex_types.h"
#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;
using namespace StoneX;

TEST(StoneXTestJSON, TestApi2FALogonOnResponseDTO) {
  Api2FALogonOnResponseDTO s;
  json::parse(json(s).dump()).template get<Api2FALogonOnResponseDTO>();
}

TEST(StoneXTestJSON, TestApiLogOnResponseDTO) {
  ApiLogOnResponseDTO s;
  json::parse(json(s).dump()).template get<ApiLogOnResponseDTO>();
}

TEST(StoneXTestJSON, TestLegalPartyDTO) {
  LegalPartyDTO s;
  json::parse(json(s).dump()).template get<LegalPartyDTO>();
}

TEST(StoneXTestJSON, TestTimestamp) {
  Timestamp s;
  json::parse(json(s).dump()).template get<Timestamp>();
}

TEST(StoneXTestJSON, TestApiClientAccountDTO) {
  ApiClientAccountDTO s;
  json::parse(json(s).dump()).template get<ApiClientAccountDTO>();
}

TEST(StoneXTestJSON, TestApiAccountHolderDTO) {
  ApiAccountHolderDTO s;
  json::parse(json(s).dump()).template get<ApiAccountHolderDTO>();
}

TEST(StoneXTestJSON, TestApiTradingAccountDTO) {
  ApiTradingAccountDTO s;
  json::parse(json(s).dump()).template get<ApiTradingAccountDTO>();
}

TEST(StoneXTestJSON, TestApiAccountOperatorDTO) {
  ApiAccountOperatorDTO s;
  json::parse(json(s).dump()).template get<ApiAccountOperatorDTO>();
}

TEST(StoneXTestJSON, TestApiClientAccountTokenDTO) {
  ApiClientAccountTokenDTO s;
  json::parse(json(s).dump()).template get<ApiClientAccountTokenDTO>();
}

TEST(StoneXTestJSON, TestApiContractDTO) {
  ApiContractDTO s;
  json::parse(json(s).dump()).template get<ApiContractDTO>();
}

TEST(StoneXTestJSON, TestApiRestrictionDTO) {
  ApiRestrictionDTO s;
  json::parse(json(s).dump()).template get<ApiRestrictionDTO>();
}

TEST(StoneXTestJSON, TestLogonUser) {
  LogonUser s;
  json::parse(json(s).dump()).template get<LogonUser>();
}

TEST(StoneXTestJSON, TestLinkedAccountResult) {
  LinkedAccountResult s;
  json::parse(json(s).dump()).template get<LinkedAccountResult>();
}

TEST(StoneXTestJSON, TestCashEquity) {
  CashEquity s;
  json::parse(json(s).dump()).template get<CashEquity>();
}

TEST(StoneXTestJSON, TestAccountResult) {
  AccountResult s;
  json::parse(json(s).dump()).template get<AccountResult>();
}

TEST(StoneXTestJSON, TestClientAccountMarginResponseDTO) {
  ClientAccountMarginResponseDTO s;
  json::parse(json(s).dump()).template get<ClientAccountMarginResponseDTO>();
}

TEST(StoneXTestJSON, TestApiMarketEodDTO) {
  ApiMarketEodDTO s;
  json::parse(json(s).dump()).template get<ApiMarketEodDTO>();
}

TEST(StoneXTestJSON, TestApiDateTimeOffsetDTO) {
  ApiDateTimeOffsetDTO s;
  json::parse(json(s).dump()).template get<ApiDateTimeOffsetDTO>();
}

TEST(StoneXTestJSON, TestApiTradingDayTimesDTO) {
  ApiTradingDayTimesDTO s;
  json::parse(json(s).dump()).template get<ApiTradingDayTimesDTO>();
}

TEST(StoneXTestJSON, TestApiMarketSpreadDTO) {
  ApiMarketSpreadDTO s;
  json::parse(json(s).dump()).template get<ApiMarketSpreadDTO>();
}

TEST(StoneXTestJSON, TestApiStepMarginBandDTO) {
  ApiStepMarginBandDTO s;
  json::parse(json(s).dump()).template get<ApiStepMarginBandDTO>();
}

TEST(StoneXTestJSON, TestApiStepMarginDTO) {
  ApiStepMarginDTO s;
  json::parse(json(s).dump()).template get<ApiStepMarginDTO>();
}
TEST(StoneXTestJSON, TestApiFxFinancingDTO) {
  ApiFxFinancingDTO s;
  json::parse(json(s).dump()).template get<ApiFxFinancingDTO>();
}
TEST(StoneXTestJSON, TestApiKnockoutDTO) {
  ApiKnockoutDTO s;
  json::parse(json(s).dump()).template get<ApiKnockoutDTO>();
}
TEST(StoneXTestJSON, TestCorporateActionsDTO) {
  CorporateActionsDTO s;
  json::parse(json(s).dump()).template get<CorporateActionsDTO>();
}
TEST(StoneXTestJSON, TestMarketPricesDTO) {
  MarketPricesDTO s;
  json::parse(json(s).dump()).template get<MarketPricesDTO>();
}
TEST(StoneXTestJSON, TestIdentifiersDTO) {
  IdentifiersDTO s;
  json::parse(json(s).dump()).template get<IdentifiersDTO>();
}
TEST(StoneXTestJSON, TestApiMarketInformationDTO) {
  ApiMarketInformationDTO s;
  json::parse(json(s).dump()).template get<ApiMarketInformationDTO>();
}
TEST(StoneXTestJSON, TestApiMarketTagDTO) {
  ApiMarketTagDTO s;
  json::parse(json(s).dump()).template get<ApiMarketTagDTO>();
}
TEST(StoneXTestJSON, TestFullMarketInformationSearchWithTagsResponseDTO) {
  FullMarketInformationSearchWithTagsResponseDTO s;
  json::parse(json(s).dump()).template get<FullMarketInformationSearchWithTagsResponseDTO>();
}
TEST(StoneXTestJSON, TestPriceBarDTO) {
  PriceBarDTO s;
  json::parse(json(s).dump()).template get<PriceBarDTO>();
}
TEST(StoneXTestJSON, TestGetPriceBarResponseDTO) {
  GetPriceBarResponseDTO s;
  json::parse(json(s).dump()).template get<GetPriceBarResponseDTO>();
}