#include "Logger.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>

TEST(GeneralTest, TestLogger) {
  auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  auto console_sink2 = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

  auto logger = std::make_shared<StructuredLogger>("test_logger", console_sink);
  auto separate_logger = std::make_shared<StructuredLogger>("other_logger", console_sink2);
  auto new_logger = logger->bind("info", "test", "number", 10);
  new_logger->set_name("new_logger");
  auto new_logger2 = new_logger->bind("number", 30);
  new_logger->get_spdlogger()->set_level(spdlog::level::debug);

  auto print = [&]() {
    logger->info("hi");
    new_logger->info("ho");
    new_logger2->info("ho");
    separate_logger->info("hello");
    logger->debug("hi");
    new_logger->debug("ho");
    new_logger2->debug("ho");
    separate_logger->debug("hello");
    logger->warn("hi");
    new_logger->warn("ho");
    new_logger2->warn("ho");
    separate_logger->warn("hello");
    logger->error("hi");
    new_logger->error("ho");
    new_logger2->error("ho");
    separate_logger->error("hello");
  };

  print();

  logger->serialize();
  print();

  logger->serialize(false);
  print();
}