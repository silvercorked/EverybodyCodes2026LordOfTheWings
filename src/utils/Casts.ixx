
export module Utils.Casts;

import <type_traits>;
import <bit>;

export
template <typename T>
constexpr
T implicit_cast(typename std::type_identity<T>::type val) {
	return val;
}

export
template <typename U, typename T>
constexpr
U pun_cast(const T& val) {
	return std::bit_cast<U>(val);
}
