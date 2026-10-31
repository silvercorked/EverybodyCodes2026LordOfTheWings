
export module Quest2;

import Utils;
import BaseQuest;

import <utility>;
import <vector>;
import <map>;
import <unordered_map>;
import <string>;
import <set>;

export
struct Quest2 : public BaseQuest<u32, u64, u64> {
	Quest2();

protected:
	auto [[nodiscard]] solution1(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> final;
	auto [[nodiscard]] solution2(const std::string&) const noexcept -> std::expected<u64, QuestUnimplemented> final;
	auto [[nodiscard]] solution3(const std::string&) const noexcept -> std::expected<u64, QuestUnimplemented> final;
};

namespace Q2Helpers {
	struct Group {
		bool softerThan; // '<' is operator
		std::pair<u32, u32> values;
	};
	auto harderFrequency(const std::vector<Group>&) -> std::map<u32, u32>; // k = how often a value was soft, v is value
	auto unorderedHarderFrequency(const std::vector<Group>&) -> std::unordered_map<u32, u32>; // k is value, v is how often soft. unordered

	auto harderMap(const std::vector<Group>&) -> std::unordered_map<u32, std::set<u32>>;
	auto refineHarderMap(std::unordered_map<u32, std::set<u32>>&) -> void;
};
