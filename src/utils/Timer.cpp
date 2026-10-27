
#include "Timer.hpp"

auto Timer::prettyPrintTime(std::chrono::nanoseconds nano) -> const std::string {
	std::string ret;
	auto micro = std::chrono::floor<std::chrono::microseconds>(nano);
	nano -= micro;
	ret = std::format("{}", nano);
	auto milli = std::chrono::floor<std::chrono::milliseconds>(micro);
	micro -= milli;
	if (micro.count() == 0 && milli.count() == 0) return ret;
	ret.insert(0, std::format("{} ", micro));
	auto seconds = std::chrono::floor<std::chrono::seconds>(milli);
	milli -= seconds;
	if (milli.count() == 0 && seconds.count() == 0) return ret;
	ret.insert(0, std::format("{} ", milli));
	auto minutes = std::chrono::floor<std::chrono::minutes>(seconds);
	seconds -= minutes;
	if (seconds.count() == 0 && minutes.count() == 0) return ret;
	ret.insert(0, std::format("{} ", seconds));
	auto hours = std::chrono::floor<std::chrono::hours>(minutes);
	minutes -= hours;
	if (minutes.count() == 0 && hours.count() == 0) return ret;
	ret.insert(0, std::format("{} ", minutes));
	auto days = std::chrono::floor<std::chrono::hours>(hours);
	hours -= days;
	if (hours.count() == 0 && days.count() == 0) return ret;
	ret.insert(0, std::format("{} ", hours));
	auto weeks = std::chrono::floor<std::chrono::hours>(days);
	days -= weeks;
	if (days.count() == 0 && weeks.count() == 0) return ret;
	ret.insert(0, std::format("{} ", days));
	auto months = std::chrono::floor<std::chrono::hours>(weeks);
	weeks -= months;
	if (weeks.count() == 0 && months.count() == 0) return ret;
	ret.insert(0, std::format("{} ", weeks));
	auto years = std::chrono::floor<std::chrono::hours>(months);
	months -= years;
	if (months.count() == 0 && years.count() == 0) return ret;
	ret.insert(0, std::format("{} ", months));
	if (years.count() == 0) return ret;
	ret.insert(0, std::format("{} ", years));
	return ret;
}
