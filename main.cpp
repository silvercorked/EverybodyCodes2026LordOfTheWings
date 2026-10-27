
#include "src/quests/quest1/q1.hpp"

#include <print>

auto main() -> int {
	auto a = Quest1::solution1();
	auto b = Quest1::solution2();
	auto c = Quest1::solution3();

	std::println("out 1: {}", a);
	std::println("out 2: {}", b);
	std::println("out 3: {}", c);
}
