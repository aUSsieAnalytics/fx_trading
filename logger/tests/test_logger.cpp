#include "Logger.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(GeneralTest, TestLogger) {
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  auto logger = std::make_shared<Logger>("test_logger", console_sink);
  auto new_logger = logger->bind("info", "test");
  logger->info("hi");
  new_logger->info("ho");

  logger->serialize();
  logger->info("hi");
  new_logger->info("ho");

  logger->serialize(false);
  logger->info("hi");
  new_logger->info("ho");
}