#include "Logger.hpp"
#include <gtest/gtest.h>
#include <iostream>

TEST(GeneralTest, TestLogger) {
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  auto console_sink2 = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  auto logger = std::make_shared<Logger>("test_logger", console_sink);
  auto separate_logger = std::make_shared<Logger>("other_logger", console_sink2);
  auto new_logger = logger->bind("info", "test", "number", 10);
  auto new_logger2 = new_logger->bind("number", 30);
  new_logger->get_spdlogger()->set_level(spdlog::level::debug);

  logger->info("hi");
  new_logger->info("ho");
  separate_logger->info("hello");
  logger->debug("hi");
  new_logger->debug("ho");
  separate_logger->debug("hello");

  logger->serialize();

  logger->info("hi");
  new_logger->info("ho");
  new_logger2->info("wazzup");
  separate_logger->info("hello");
  logger->debug("hi");
  new_logger->debug("ho");
  separate_logger->debug("hello");

  logger->serialize(false);

  logger->info("hi");
  new_logger->info("ho");
  separate_logger->info("hello");
  logger->debug("hi");
  new_logger->debug("ho");
  separate_logger->debug("hello");
}