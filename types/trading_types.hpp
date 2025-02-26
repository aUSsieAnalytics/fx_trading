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