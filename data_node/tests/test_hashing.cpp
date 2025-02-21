#include "sha256.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(HashingTest, TestHashOutput) {
  string input = "grape";
  string output1 = sha256(input);
  ASSERT_EQ(output1, "0f78fcc486f5315418fbf095e71c0675ee07d318e5ac4d150050cd8e57966496");

  string huge_string((512 / 8) * 5, 'x');
  ASSERT_EQ(sha256(huge_string),
            "e894706a0b642bfb3eb07c97fee00b18ab1581ff661f1c4473f55e6afe1c8982");
}