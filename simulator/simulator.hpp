#pragma once

#include <time.h>

class FXSimulator {
  time_t _current_time;
  time_t _end_time;
  time_t _start_time;

public:
  FXSimulator();
  time_t current_time();
  time_t end_time();
  time_t start_time();
};
