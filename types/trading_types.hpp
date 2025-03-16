#pragma once
#include <array>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

template <typename> struct is_std_vector : std::false_type {};

template <typename T> struct is_std_vector<std::vector<T>> : std::true_type {};

template <typename T>
void fill_from_json(std::vector<T> &vector, const std::string &name, const json &j) {
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

template <typename T>
typename std::enable_if<!is_std_vector<T>::value, void>::type
fill_from_json(T &member, const std::string &name, const json &j) {
  auto item = j.at(name);
  if (item != nullptr) {
    item.get_to(member);
  }
}

enum CandleStickPrice { OPEN, CLOSE, HIGH, LOW };
constexpr std::array<std::pair<CandleStickPrice, const char *>, 4> price_to_string = {
    {{OPEN, "OPEN"}, {CLOSE, "CLOSE"}, {HIGH, "HIGH"}, {LOW, "LOW"}}};

constexpr const std::string_view price_lookup(CandleStickPrice price) {
  return price_to_string[price].second;
}

constexpr const std::ostream &operator<<(std::ostream &stream, const CandleStickPrice &price) {
  return stream << price_lookup(price);
}

namespace std {
constexpr const std::string to_string(const CandleStickPrice &price) {
  return std::string(price_lookup(price));
}
} // namespace std

enum PriceType { BID, MID, ASK };
constexpr std::array<std::pair<PriceType, const char *>, 4> price_type_to_string = {
    {{BID, "BID"}, {MID, "MID"}, {ASK, "ASK"}}};

constexpr const std::string_view price_type_lookup(PriceType price) {
  return price_type_to_string[price].second;
}

constexpr const std::ostream &operator<<(std::ostream &stream, const PriceType &price) {
  return stream << price_type_lookup(price);
}

namespace std {
constexpr const std::string to_string(const PriceType &price) {
  return std::string(price_type_lookup(price));
}
} // namespace std

enum CandlePeriodUnit { MINUTE, HOUR, DAY };
constexpr std::array<std::pair<CandlePeriodUnit, const char *>, 4> candle_period_to_string = {
    {{MINUTE, "MINUTE"}, {HOUR, "HOUR"}, {DAY, "DAY"}}};

constexpr const std::string_view candle_period_lookup(CandlePeriodUnit unit) {
  return candle_period_to_string[unit].second;
}

constexpr const std::ostream &operator<<(std::ostream &stream, const CandlePeriodUnit &unit) {
  return stream << candle_period_lookup(unit);
}

namespace std {
constexpr const std::string to_string(const CandlePeriodUnit &unit) {
  return std::string(candle_period_lookup(unit));
}
} // namespace std

enum OrderDirection { BUY, SELL };
constexpr std::array<std::pair<OrderDirection, const char *>, 2> order_direction_to_string = {
    {{BUY, "BUY"}, {SELL, "SELL"}}};

constexpr const std::string_view order_direction_lookup(OrderDirection direction) {
  return order_direction_to_string[direction].second;
}

constexpr const std::ostream &operator<<(std::ostream &stream, const OrderDirection &direction) {
  return stream << order_direction_lookup(direction);
}

namespace std {
constexpr const std::string to_string(const OrderDirection &direction) {
  return std::string(order_direction_lookup(direction));
}
} // namespace std

enum Broker { OANDA, FOREXCOM };
constexpr std::array<std::pair<Broker, const char *>, 2> broker_to_string = {
    {{OANDA, "OANDA"}, {FOREXCOM, "FOREXCOM"}}};

constexpr const std::string_view broker_lookup(Broker broker) {
  return broker_to_string[broker].second;
}

constexpr const std::ostream &operator<<(std::ostream &stream, const Broker &broker) {
  return stream << broker_lookup(broker);
}

namespace std {
constexpr const std::string to_string(const Broker &broker) {
  return std::string(broker_lookup(broker));
}
} // namespace std

struct CandleStick {
  double open;
  double close;
  double high;
  double low;

  template <typename A = double, typename B = double, typename C = double, typename D = double>
  CandleStick(A open = 0, B close = 0, C high = 0, D low = 0)
      : open(static_cast<double>(open)), close(static_cast<double>(close)),
        high(static_cast<double>(high)), low(static_cast<double>(low)) {}

  template <typename T> CandleStick operator+(const T &rhs) const {
    return {
        this->open + rhs,
        this->close + rhs,
        this->high + rhs,
        this->low + rhs,
    };
  }

  CandleStick operator+(const CandleStick &rhs) const {
    return {this->open + rhs.open, this->close + rhs.close, this->high + rhs.high,
            this->low + rhs.low};
  }

  template <typename T> CandleStick operator-(const T &rhs) const {
    return {
        this->open - rhs,
        this->close - rhs,
        this->high - rhs,
        this->low - rhs,
    };
  }

  CandleStick operator-(const CandleStick &rhs) const {
    return {this->open - rhs.open, this->close - rhs.close, this->high - rhs.high,
            this->low - rhs.low};
  }

  template <typename T> CandleStick operator*(const T &rhs) const {
    return {
        this->open * rhs,
        this->close * rhs,
        this->high * rhs,
        this->low * rhs,
    };
  }

  CandleStick operator*(const CandleStick &rhs) const {
    return {this->open * rhs.open, this->close * rhs.close, this->high * rhs.high,
            this->low * rhs.low};
  }

  template <typename T> CandleStick operator/(const T &rhs) const {
    return {
        this->open / rhs,
        this->close / rhs,
        this->high / rhs,
        this->low / rhs,
    };
  }

  CandleStick operator/(const CandleStick &rhs) const {
    return {this->open / rhs.open, this->close / rhs.close, this->high / rhs.high,
            this->low / rhs.low};
  }

  template <typename T> CandleStick &operator+=(const T &rhs) {
    this->open += rhs;
    this->close += rhs;
    this->high += rhs;
    this->low += rhs;
    return *this;
  }

  CandleStick &operator+=(const CandleStick &rhs) {
    this->open += rhs.open;
    this->close += rhs.close;
    this->high += rhs.high;
    this->low += rhs.low;
    return *this;
  }

  template <typename T> CandleStick &operator-=(const T &rhs) {
    this->open -= rhs;
    this->close -= rhs;
    this->high -= rhs;
    this->low -= rhs;
    return *this;
  }

  CandleStick &operator-=(const CandleStick &rhs) {
    this->open -= rhs.open;
    this->close -= rhs.close;
    this->high -= rhs.high;
    this->low -= rhs.low;
    return *this;
  }

  template <typename T> CandleStick &operator/=(const T &rhs) {
    this->open /= rhs;
    this->close /= rhs;
    this->high /= rhs;
    this->low /= rhs;
    return *this;
  }

  CandleStick &operator/=(const CandleStick &rhs) {
    this->open /= rhs.open;
    this->close /= rhs.close;
    this->high /= rhs.high;
    this->low /= rhs.low;
    return *this;
  }

  template <typename T> CandleStick &operator*=(const T &rhs) {
    this->open *= rhs;
    this->close *= rhs;
    this->high *= rhs;
    this->low *= rhs;
    return *this;
  }

  CandleStick &operator*=(const CandleStick &rhs) {
    this->open *= rhs.open;
    this->close *= rhs.close;
    this->high *= rhs.high;
    this->low *= rhs.low;
    return *this;
  }
};

inline void from_json(const json &j, CandleStick &resp) {
  if (j == nullptr)
    return;
  fill_from_json(resp.open, "open", j);
  fill_from_json(resp.close, "close", j);
  fill_from_json(resp.high, "high", j);
  fill_from_json(resp.low, "low", j);
}
inline void to_json(json &j, const CandleStick &o) {
  j = json{
      {"open", o.open},
      {"close", o.close},
      {"high", o.high},
      {"low", o.low},
  };
}
enum Granularity {
  S5,
  S10,
  S15,
  S30,
  M1,
  M2,
  M4,
  M5,
  M10,
  M15,
  M30,
  H1,
  H2,
  H3,
  H4,
  H6,
  H8,
  H12,
  D,
  W,
  M
};

constexpr std::array<std::pair<Granularity, const char *>, 21> granularity_to_string_mapping = {
    {{S5, "S5"}, {S10, "S10"}, {S15, "S15"}, {S30, "S30"}, {M1, "M1"}, {M2, "M2"}, {M4, "M4"},
     {M5, "M5"}, {M10, "M10"}, {M15, "M15"}, {M30, "M30"}, {H1, "H1"}, {H2, "H2"}, {H3, "H3"},
     {H4, "H4"}, {H6, "H6"},   {H8, "H8"},   {H12, "H12"}, {D, "D"},   {W, "W"},   {M, "M"}}};

constexpr const std::string_view granularity_to_string(Granularity granularity) {
  return granularity_to_string_mapping[granularity].second;
}

constexpr const std::ostream &operator<<(std::ostream &stream, const Granularity granularity) {
  return stream << granularity_to_string(granularity);
}

namespace std {
constexpr const std::string to_string(const Granularity &granularity) {
  return std::string(granularity_to_string(granularity));
}
} // namespace std

enum ForexPair {
  AUDCAD,
  AUDCHF,
  AUDHKD,
  AUDJPY,
  AUDNZD,
  AUDSGD,
  AUDUSD,
  CADCHF,
  CADHKD,
  CADJPY,
  CADSGD,
  CHFHKD,
  CHFJPY,
  CHFZAR,
  EURAUD,
  EURCAD,
  EURCHF,
  EURCZK,
  EURDKK,
  EURGBP,
  EURHKD,
  EURHUF,
  EURJPY,
  EURNOK,
  EURNZD,
  EURPLN,
  EURSEK,
  EURSGD,
  EURTRY,
  EURUSD,
  EURZAR,
  GBPAUD,
  GBPCAD,
  GBPCHF,
  GBPHKD,
  GBPJPY,
  GBPNZD,
  GBPPLN,
  GBPSGD,
  GBPUSD,
  GBPZAR,
  HKDJPY,
  NZDCAD,
  NZDCHF,
  NZDHKD,
  NZDJPY,
  NZDSGD,
  NZDUSD,
  SGDCHF,
  SGDJPY,
  TRYJPY,
  USDCAD,
  USDCHF,
  USDCNH,
  USDDKK,
  USDHKD,
  USDHUF,
  USDJPY,
  USDMXN,
  USDNOK,
  USDPLN,
  USDSEK,
  USDSGD,
  USDTHB,
  USDTRY,
  USDZAR,
  ZARJPY
};

constexpr std::array<std::pair<ForexPair, const char *>, 67> forex_pair_to_string = {
    {{AUDCAD, "AUDCAD"}, {AUDCHF, "AUDCHF"}, {AUDHKD, "AUDHKD"}, {AUDJPY, "AUDJPY"},
     {AUDNZD, "AUDNZD"}, {AUDSGD, "AUDSGD"}, {AUDUSD, "AUDUSD"}, {CADCHF, "CADCHF"},
     {CADHKD, "CADHKD"}, {CADJPY, "CADJPY"}, {CADSGD, "CADSGD"}, {CHFHKD, "CHFHKD"},
     {CHFJPY, "CHFJPY"}, {CHFZAR, "CHFZAR"}, {EURAUD, "EURAUD"}, {EURCAD, "EURCAD"},
     {EURCHF, "EURCHF"}, {EURCZK, "EURCZK"}, {EURDKK, "EURDKK"}, {EURGBP, "EURGBP"},
     {EURHKD, "EURHKD"}, {EURHUF, "EURHUF"}, {EURJPY, "EURJPY"}, {EURNOK, "EURNOK"},
     {EURNZD, "EURNZD"}, {EURPLN, "EURPLN"}, {EURSEK, "EURSEK"}, {EURSGD, "EURSGD"},
     {EURTRY, "EURTRY"}, {EURUSD, "EURUSD"}, {EURZAR, "EURZAR"}, {GBPAUD, "GBPAUD"},
     {GBPCAD, "GBPCAD"}, {GBPCHF, "GBPCHF"}, {GBPHKD, "GBPHKD"}, {GBPJPY, "GBPJPY"},
     {GBPNZD, "GBPNZD"}, {GBPPLN, "GBPPLN"}, {GBPSGD, "GBPSGD"}, {GBPUSD, "GBPUSD"},
     {GBPZAR, "GBPZAR"}, {HKDJPY, "HKDJPY"}, {NZDCAD, "NZDCAD"}, {NZDCHF, "NZDCHF"},
     {NZDHKD, "NZDHKD"}, {NZDJPY, "NZDJPY"}, {NZDSGD, "NZDSGD"}, {NZDUSD, "NZDUSD"},
     {SGDCHF, "SGDCHF"}, {SGDJPY, "SGDJPY"}, {TRYJPY, "TRYJPY"}, {USDCAD, "USDCAD"},
     {USDCHF, "USDCHF"}, {USDCNH, "USDCNH"}, {USDDKK, "USDDKK"}, {USDHKD, "USDHKD"},
     {USDHUF, "USDHUF"}, {USDJPY, "USDJPY"}, {USDMXN, "USDMXN"}, {USDNOK, "USDNOK"},
     {USDPLN, "USDPLN"}, {USDSEK, "USDSEK"}, {USDSGD, "USDSGD"}, {USDTHB, "USDTHB"},
     {USDTRY, "USDTRY"}, {USDZAR, "USDZAR"}, {ZARJPY, "ZARJPY"}}};

constexpr const std::string_view forex_lookup(ForexPair pair) {
  return forex_pair_to_string[pair].second;
}

constexpr const std::ostream &operator<<(std::ostream &stream, const ForexPair &pair) {
  return stream << forex_lookup(pair);
}

namespace std {
constexpr const std::string to_string(const ForexPair &pair) {
  return std::string(forex_lookup(pair));
}
} // namespace std

enum Currency {
  AUD,
  CAD,
  CHF,
  CNH,
  CZK,
  DKK,
  EUR,
  GBP,
  HKD,
  HUF,
  JPY,
  MXN,
  NOK,
  NZD,
  PLN,
  SEK,
  SGD,
  THB,
  TRY,
  USD,
  ZAR
};

constexpr std::array<std::pair<Currency, const char *>, 21> currency_to_string = {
    {{AUD, "AUD"}, {CAD, "CAD"}, {CHF, "CHF"}, {CNH, "CNH"}, {CZK, "CZK"}, {DKK, "DKK"},
     {EUR, "EUR"}, {GBP, "GBP"}, {HKD, "HKD"}, {HUF, "HUF"}, {JPY, "JPY"}, {MXN, "MXN"},
     {NOK, "NOK"}, {NZD, "NZD"}, {PLN, "PLN"}, {SEK, "SEK"}, {SGD, "SGD"}, {THB, "THB"},
     {TRY, "TRY"}, {USD, "USD"}, {ZAR, "ZAR"}}};

constexpr const std::string_view currency_lookup(Currency currency) {
  return currency_to_string[currency].second;
}

constexpr const std::ostream &operator<<(std::ostream &stream, const Currency &currency) {
  return stream << currency_lookup(currency);
}

namespace std {
constexpr const std::string to_string(const Currency &currency) {
  return std::string(currency_lookup(currency));
}

} // namespace std