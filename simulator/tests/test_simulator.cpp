#include "simulator.hpp"
#include <chrono>
#include <gtest/gtest.h>

using namespace std;

TEST(SimulatorTest, Initialization) {
  auto simulator = FXSimulator();
  ASSERT_NEAR(simulator.current_time(),
              chrono::system_clock::to_time_t(chrono::system_clock::now()), 1e2);
}