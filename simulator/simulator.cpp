#include "simulator.hpp"
#include <chrono>

FXSimulator::FXSimulator(): _start_time(0), _end_time(0) {
  _current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

time_t FXSimulator::current_time() { return _current_time; }