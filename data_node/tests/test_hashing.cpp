#include "sha256.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(HashingTest, TestHashOutput) {
  string input = "grape";
  string output1 = sha256(input);
  ASSERT_EQ(output1, "0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496");
}