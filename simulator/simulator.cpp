#include "simulator.hpp"
#include <chrono>

FXSimulator::FXSimulator() : _end_time(0), _start_time(0) {
  _current_time = chrono::system_clock::to_time_t(chrono::system_clock::now());
}

time_t FXSimulator::current_time() { return _current_time; }
time_t FXSimulator::start_time() { return _start_time; }
time_t FXSimulator::end_time() { return _end_time; }