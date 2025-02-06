#pragma once

#include <time.h>

using namespace std;

class FXSimulator {
  time_t _current_time;

public:
  FXSimulator();
  time_t current_time();
};
