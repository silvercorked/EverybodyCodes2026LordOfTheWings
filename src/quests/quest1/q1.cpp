
#include "q1.hpp"

#include "../../utils/Timer.hpp"
#include "../../utils/FileReadUtils.hpp"

#include <print>
#include <string>
#include <ranges>

using namespace FileReadUtils;

namespace Quest1 {
	auto [[nodiscard]] solution1() -> u32 {
		auto problem = parseFileCSL(readProblemFile(2026, 1, 1)) | std::ranges::views::transform([](const std::string& val) -> i32 { return std::stoi(val); });
		std::println("problem 2026, q1, p1:");
		Timer::Timer t{};
		u32 accum = 0;
		for (const auto& count : problem) {
			auto next = Internal::nextSquare(count);

#ifdef _DEBUG
			std::println("count: {}, nextSquare: {} ({}), diff: {}", count, next, next * next, (next * next) - count);
#endif
			accum += (next * next) - count;
		}
		std::println("\ttime p1: {}", t.getElapsedSinceConstruction());
		return accum;
	}

	auto [[nodiscard]] solution2() -> u32 {
		auto problem = parseFileCSL(readProblemFile(2026, 1, 2)) | std::ranges::views::transform([](const std::string& val) -> i32 { return std::stoi(val); });
		std::println("problem 2026, q1, p2:");
		Timer::Timer t{};
		u32 accum = 0;
		for (const auto& count : problem) {
			auto next = Internal::nextPerimeter(count, 3);
#ifdef _DEBUG
			std::println("count: {}, nextSquare: {} ({}), diff: {}, perimeter: {}, diff:{}", count, next, next * next, (next * next) - count, (next - 1) * 4, ((next - 1) * 4) - count);
#endif
			accum += ((next - 1) * 4) - count;
		}
		std::println("\ttime p2: {}", t.getElapsedSinceConstruction());
		return accum;
	}

	auto [[nodiscard]] solution3() -> u32 {
		auto problem = parseFileCSL(readProblemFile(2026, 1, 1)) | std::ranges::views::transform([](const std::string& val) -> i32 { return std::stoi(val); });
		std::println("problem 2026, q1, p3:");
		Timer::Timer t{};
		u32 accum = 0;
		for (const auto& count : problem) {
			auto next = Internal::nextOddSquareMinus1(count, 3);
#ifdef _DEBUG
			std::println("count: {}, nextSquare: {} ({}), diff: {}", count, next, (next * next - 1), ((next * next) - 1) - count);
#endif
			accum += ((next * next) - 1) - count;
		}
		std::println("\ttime: {}", t.getElapsedSinceConstruction());
		return accum;
	}

	namespace Internal {
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
}