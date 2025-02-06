#include "simulator.hpp"
#include <chrono>

FXSimulator::FXSimulator() {
  _current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

time_t FXSimulator::current_time() { return _current_time; }