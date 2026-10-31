
export module Quest1;

import Utils;
import BaseQuest;

import <string>;
import <expected>;

export
struct Quest1 : public BaseQuest<u32> {
	Quest1();

protected:
	auto [[nodiscard]] solution1(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> final;
	auto [[nodiscard]] solution2(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> final;
	auto [[nodiscard]] solution3(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> final;
};

namespace Q1Helpers {
	auto nextSquare(u32 in, u32 start = 1) -> u32;
	auto nextPerimeter(u32 in, u32 start = 1) -> u32;
	auto nextOddSquareMinus1(u32 in, u32 start = 1) -> u32;
};
