#pragma once
#include <random>
#include <sstream>

namespace uuid {
static inline std::random_device rd;
static inline std::mt19937 gen(rd());
static inline std::uniform_int_distribution<> dis(0, 15);
static inline std::uniform_int_distribution<> dis2(8, 11);

std::string generate_uuid_v4();
} // namespace uuid