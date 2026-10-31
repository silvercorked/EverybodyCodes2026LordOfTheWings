
module Quest1;

import Utils;

#ifdef _DEBUG
import <print>;
#endif

import <string>;
import <ranges>;

using namespace FileReadUtils;

Quest1::Quest1() : BaseQuest{ 2026, 1 } {}

auto [[nodiscard]] Quest1::solution1(const std::string& p) const noexcept -> std::expected<u32, QuestUnimplemented> {
	auto problem = parseFileCSL(p) | std::ranges::views::transform([](const std::string& val) -> i32 { return std::stoi(val); });
#ifdef _DEBUG
	std::println("problem 2026, q1, p1:");
#endif
	u32 accum = 0;
	for (const auto& count : problem) {
		auto next = Q1Helpers::nextSquare(count);
#ifdef _DEBUG
		std::println("count: {}, nextSquare: {} ({}), diff: {}", count, next, next * next, (next * next) - count);
#endif
		accum += (next * next) - count;
	}
	return accum;
}

auto [[nodiscard]] Quest1::solution2(const std::string& p) const noexcept -> std::expected<u32, QuestUnimplemented> {
	auto problem = parseFileCSL(p) | std::ranges::views::transform([](const std::string& val) -> i32 { return std::stoi(val); });
#ifdef _DEBUG
	std::println("problem 2026, q1, p2:");
#endif
	u32 accum = 0;
	for (const auto& count : problem) {
		auto next = Q1Helpers::nextPerimeter(count, 3);
#ifdef _DEBUG
		std::println("count: {}, nextSquare: {} ({}), diff: {}, perimeter: {}, diff:{}", count, next, next * next, (next * next) - count, (next - 1) * 4, ((next - 1) * 4) - count);
#endif
		accum += ((next - 1) * 4) - count;
	}
	return accum;
}

auto [[nodiscard]] Quest1::solution3(const std::string& p) const noexcept -> std::expected<u32, QuestUnimplemented> {
	auto problem = parseFileCSL(p) | std::ranges::views::transform([](const std::string& val) -> i32 { return std::stoi(val); });
#ifdef _DEBUG
	std::println("problem 2026, q1, p3:");
#endif
	u32 accum = 0;
	for (const auto& count : problem) {
		auto next = Q1Helpers::nextOddSquareMinus1(count, 3);
#ifdef _DEBUG
		std::println("count: {}, nextSquare: {} ({}), diff: {}", count, next, (next * next - 1), ((next * next) - 1) - count);
#endif
		accum += ((next * next) - 1) - count;
	}
	return accum;
}

namespace Q1Helpers {
	auto nextSquare(u32 in, u32 start) -> u32 {
		u32 candidate = start;
		while (candidate * candidate < in) {
			++candidate;
		}
		return candidate;
	}

	auto nextPerimeter(u32 in, u32 start) -> u32 {
		u32 candidate = start;
		while ((candidate - 1) * 4 < in) {
			++candidate;
		}
		return candidate;
	}

	auto nextOddSquareMinus1(u32 in, u32 start) -> u32 {
		u32 candidate = start % 2 == 0 ? start + 1 : start;
		while ((candidate * candidate) - 1 < in) {
			candidate += 2;
		}
		return candidate;
	}
}
