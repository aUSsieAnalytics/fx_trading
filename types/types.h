#include <ctime>

struct CandleStick {
  double open;
  double close;
  double high;
  double low;
};

struct Price {
  CandleStick bid;
  CandleStick mid;
  CandleStick ask;
};
