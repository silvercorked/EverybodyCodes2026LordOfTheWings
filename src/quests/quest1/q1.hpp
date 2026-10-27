#pragma once

#include "../../utils/PrimitiveTypes.hpp"

namespace Quest1 {
	auto [[nodiscard]] solution1() -> u32;
	auto [[nodiscard]] solution2() -> u32;
	auto [[nodiscard]] solution3() -> u32;

	namespace Internal {
		auto nextSquare(u32 in, u32 start = 1) -> u32;
		auto nextPerimeter(u32 in, u32 start = 1) -> u32;
		auto nextOddSquareMinus1(u32 in, u32 start = 1) -> u32;
	};
}