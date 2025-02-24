#include "DataNode.hpp"
#include <gtest/gtest.h>

// Class for test fixture
class DataNodeTest : public ::testing::Test {
protected:
  void SetUp() override { DataNodes::IDataNode::clear_registry(); }
};
