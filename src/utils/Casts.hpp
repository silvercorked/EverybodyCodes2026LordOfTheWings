#pragma once

#include <type_traits>
#include <bit>

template <typename T>
constexpr
T implicit_cast(typename std::type_identity<T>::type val) {
	return val;
}

template <typename U, typename T>
constexpr
U pun_cast(const T& val) {
	return std::bit_cast<U>(val);
}
