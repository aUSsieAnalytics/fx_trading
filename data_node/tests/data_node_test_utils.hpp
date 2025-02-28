#include "DataNode.hpp"
#include "Logger.hpp"
#include <gtest/gtest.h>

// Class for test fixture
class DataNodeTest : public ::testing::Test {
protected:
  void SetUp() override {
    DataNodes::IDataNode::clear_registry();
    auto logger = std::make_shared<StructuredLogger>(
        "DataNode", std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
    logger->get_spdlogger()->set_level(spdlog::level::debug);
    DataNodes::IDataNode::set_logger(logger);
  }
};
