#include <ctime>

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
        this->close + rhs,
        this->open + rhs,
        this->high + rhs,
        this->low + rhs,
    };
  }

  CandleStick operator+(const CandleStick &rhs) const {
    return {this->close + rhs.close, this->open + rhs.open, this->high + rhs.high,
            this->low + rhs.low};
  }

  template <typename T> CandleStick operator-(const T &rhs) const {
    return {
        this->close - rhs,
        this->open - rhs,
        this->high - rhs,
        this->low - rhs,
    };
  }

  CandleStick operator-(const CandleStick &rhs) const {
    return {this->close - rhs.close, this->open - rhs.open, this->high - rhs.high,
            this->low - rhs.low};
  }

  template <typename T> CandleStick operator*(const T &rhs) const {
    return {
        this->close * rhs,
        this->open * rhs,
        this->high * rhs,
        this->low * rhs,
    };
  }

  CandleStick operator*(const CandleStick &rhs) const {
    return {this->close * rhs.close, this->open * rhs.open, this->high * rhs.high,
            this->low * rhs.low};
  }

  template <typename T> CandleStick operator/(const T &rhs) const {
    return {
        this->close / rhs,
        this->open / rhs,
        this->high / rhs,
        this->low / rhs,
    };
  }

  CandleStick operator/(const CandleStick &rhs) const {
    return {this->close / rhs.close, this->open / rhs.open, this->high / rhs.high,
            this->low / rhs.low};
  }

  template <typename T> CandleStick &operator+=(const T &rhs) {
    this->close += rhs;
    this->open += rhs;
    this->high += rhs;
    this->low += rhs;
    return *this;
  }

  CandleStick &operator+=(const CandleStick &rhs) {
    this->close += rhs.close;
    this->open += rhs.open;
    this->high += rhs.high;
    this->low += rhs.low;
    return *this;
  }

  template <typename T> CandleStick &operator-=(const T &rhs) {
    this->close -= rhs;
    this->open -= rhs;
    this->high -= rhs;
    this->low -= rhs;
    return *this;
  }

  CandleStick &operator-=(const CandleStick &rhs) {
    this->close -= rhs.close;
    this->open -= rhs.open;
    this->high -= rhs.high;
    this->low -= rhs.low;
    return *this;
  }

  template <typename T> CandleStick &operator/=(const T &rhs) {
    this->close /= rhs;
    this->open /= rhs;
    this->high /= rhs;
    this->low /= rhs;
    return *this;
  }

  CandleStick &operator/=(const CandleStick &rhs) {
    this->close /= rhs.close;
    this->open /= rhs.open;
    this->high /= rhs.high;
    this->low /= rhs.low;
    return *this;
  }

  template <typename T> CandleStick &operator*=(const T &rhs) {
    this->close *= rhs;
    this->open *= rhs;
    this->high *= rhs;
    this->low *= rhs;
    return *this;
  }

  CandleStick &operator*=(const CandleStick &rhs) {
    this->close *= rhs.close;
    this->open *= rhs.open;
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
