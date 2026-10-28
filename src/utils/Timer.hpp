#pragma once

#include <chrono>

namespace Timer {
	template <typename T>
	concept Timer_SupportedClock = std::same_as<T, std::chrono::steady_clock> || std::same_as<T, std::chrono::system_clock>
		|| std::same_as<T, std::chrono::high_resolution_clock>;

	template <typename T>
	concept Timer_Duration = std::same_as<T, std::chrono::nanoseconds> || std::same_as<T, std::chrono::microseconds>
		|| std::same_as<T, std::chrono::milliseconds> || std::same_as<T, std::chrono::seconds>
		|| std::same_as<T, std::chrono::minutes> || std::same_as<T, std::chrono::hours>
		|| std::same_as<T, std::chrono::days> || std::same_as<T, std::chrono::weeks>
		|| std::same_as<T, std::chrono::months> || std::same_as<T, std::chrono::years>;

	auto prettyPrintTime(std::chrono::nanoseconds nano) -> const std::string;

	template <Timer_SupportedClock T = std::chrono::steady_clock>
	class Timer {
		const T::time_point _start;
		T::time_point _curr;

		template <Timer_Duration D>
		static auto getTimePointDifferenceAs(const T::time_point& a, const T::time_point& b) -> const D {
			return std::chrono::duration_cast<D>(b - a);
		}

	public:
		Timer() : _start{ T::now() }, _curr{ _start } {}
		auto set() -> const std::string {
			auto retStr = this->getElapsedSinceLastSet();
			this->_curr = T::now();
			return retStr;
		}
		auto reset() -> void { this->_curr = T::now(); }
		template <Timer_Duration D = std::chrono::nanoseconds>
		auto getElapsedSinceLastSet() const -> const std::string {
			return prettyPrintTime(
				Timer<T>::getTimePointDifferenceAs<std::chrono::nanoseconds>(this->_curr, T::now())
			);
		}
		template <Timer_Duration D = std::chrono::nanoseconds>
		auto getElapsedSinceConstruction() const -> const std::string {
			return prettyPrintTime(
				Timer<T>::getTimePointDifferenceAs<std::chrono::nanoseconds>(this->_start, T::now())
			);
		}
	};
};