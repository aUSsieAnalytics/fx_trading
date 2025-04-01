#pragma once
#include "data_node_test_utils.hpp"
#include "stonex_mock.hpp"

class StoneXDataNodeTest : public StoneXTest, public DataNodeTest {
protected:
  static void SetUpTestSuite() { StoneXTest::SetUpTestSuite(); }
  static void TearDownTestSuite() { StoneXTest::TearDownTestSuite(); }
  void SetUp() override {
    StoneXTest::SetUp();
    DataNodeTest::SetUp();
  }

  void TearDown() override {
    StoneXTest::TearDown();
    DataNodeTest::TearDown();
  }
};