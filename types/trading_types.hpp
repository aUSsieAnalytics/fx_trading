#pragma once

#include <array>
#include <iostream>

enum CandleStickPrice { OPEN, CLOSE, HIGH, LOW };

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

struct Price {
  CandleStick bid;
  CandleStick mid;
  CandleStick ask;
};

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
constexpr const std::string_view to_string(const Granularity &granularity) {
  return granularity_to_string(granularity);
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
constexpr const std::string_view to_string(const ForexPair &pair) { return forex_lookup(pair); }
} // namespace std