#pragma once

#include "../../utils/PrimitiveTypes.hpp"

#include <utility>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>

namespace Quest2 {
	auto [[nodiscard]] solution1() -> u32;
	auto [[nodiscard]] solution2() -> u64;
	auto [[nodiscard]] solution3() -> u64;

	namespace Internal {
		struct Group {
			bool softerThan; // '<' is operator
			std::pair<u32, u32> values;
		};
		auto harderFrequency(const std::vector<Group>&) -> std::map<u32, u32>; // k = how often a value was soft, v is value
		auto unorderedHarderFrequency(const std::vector<Group>&) -> std::unordered_map<u32, u32>; // k is value, v is how often soft. unordered
	
		auto harderMap(const std::vector<Group>&) -> std::unordered_map<u32, std::set<u32>>;
		auto refineHarderMap(std::unordered_map<u32, std::set<u32>>&) -> void;
	};
}