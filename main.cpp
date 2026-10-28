
#include "src/quests/quest2/q2.hpp"

#include <print>

auto main() -> int {
	auto a = Quest2::solution1();
	auto b = Quest2::solution2();
	auto c = Quest2::solution3();

	std::println("out 1: {}", a);
	std::println("out 2: {}", b);
	std::println("out 3: {}", c);
}
