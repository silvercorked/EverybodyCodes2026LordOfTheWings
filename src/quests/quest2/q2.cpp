
#include "q2.hpp"

#include "../../utils/FileReadUtils.hpp"
#include "../../utils/Timer.hpp"

#include <ranges>
#include <string>
#include <print>
#include <algorithm>

using namespace FileReadUtils;

auto [[nodiscard]] Quest2::solution1() -> u32 {
	Timer::Timer t{};
	auto problem = parseFileCSV(readProblemFile(2026, 2, 1), " ") | std::ranges::views::transform(
		[](const std::vector<std::string>& line) -> std::vector<Quest2::Internal::Group> {
			return line | std::ranges::views::transform([](const std::string& value) -> Quest2::Internal::Group {
				u32 firstVal = 0;
				char curr = value.at(firstVal);
				while (curr != '<' && curr != '>') {
					++firstVal;
					curr = value.at(firstVal);
				}
				Quest2::Internal::Group g{};
				g.softerThan = value.at(firstVal) == '<';
				g.values = std::make_pair(std::stoi(value.substr(0, firstVal)), std::stoi(value.substr(firstVal + 1, value.size())));
				return g;
			}) | std::ranges::to<std::vector>();
		}
	);
	std::println("problem 2026, q2, p1:");
	u32 accum = 0;
	for (const auto& line : problem) {
		u32 lineAccum = 0;
		auto orderedMap = Quest2::Internal::harderFrequency(line);
		for (const auto [k, v] : orderedMap) {
			lineAccum = (lineAccum * 10) + v;
		}
#ifdef _DEBUG
		std::println("lineAccum: {}", lineAccum);
#endif
		accum += lineAccum;
	}
	std::println("\ttime p1: {}", t.getElapsedSinceConstruction());
	return accum;
}

auto [[nodiscard]] Quest2::solution2() -> u64 {
	Timer::Timer t{};
	auto problem = parseFileCSV(readProblemFile(2026, 2, 2), " ") | std::ranges::views::transform(
		[](const std::vector<std::string>& line) -> std::vector<Quest2::Internal::Group> {
		return line | std::ranges::views::transform([](const std::string& value) -> Quest2::Internal::Group {
			u32 firstVal = 0;
			char curr = value.at(firstVal);
			while (curr != '<' && curr != '>') {
				++firstVal;
				curr = value.at(firstVal);
			}
			Quest2::Internal::Group g{};
			g.softerThan = value.at(firstVal) == '<';
			g.values = std::make_pair(std::stoi(value.substr(0, firstVal)), std::stoi(value.substr(firstVal + 1, value.size())));
			return g;
		}) | std::ranges::to<std::vector>();
	}
	);
	std::println("problem 2026, q2, p2:");
	u64 accum = 0;
	for (const auto& line : problem) {
		u32 lineAccum = 0;
		auto map = Quest2::Internal::harderMap(line);
		Quest2::Internal::refineHarderMap(map);
		std::vector<u32> ordered{};
		ordered.reserve(map.size());
		for (const auto [k, v] : map) {
			ordered.emplace_back(k);
		}
		std::sort(ordered.begin(), ordered.end(), [&map](const u32 a, const u32 b) -> bool {
			const auto& aSet = map.at(a);
			const auto& bSet = map.at(b);
			if (aSet.contains(b)) return true;
			else if (bSet.contains(a)) return false;
			std::unreachable();
		});
		for (const auto v : ordered) {
			lineAccum = (lineAccum * 10) + v;
		}
#ifdef _DEBUG
		std::println("lineAccum: {}", lineAccum);
#endif
		accum += lineAccum;
	}
	std::println("\ttime p2: {}", t.getElapsedSinceConstruction());
	return accum;
}

auto [[nodiscard]] Quest2::solution3() -> u64 { // this is the same as p2 but the p3 file
	Timer::Timer t{};
	auto problem = parseFileCSV(readProblemFile(2026, 2, 3), " ") | std::ranges::views::transform(
		[](const std::vector<std::string>& line) -> std::vector<Quest2::Internal::Group> {
		return line | std::ranges::views::transform([](const std::string& value) -> Quest2::Internal::Group {
			u32 firstVal = 0;
			char curr = value.at(firstVal);
			while (curr != '<' && curr != '>') {
				++firstVal;
				curr = value.at(firstVal);
			}
			Quest2::Internal::Group g{};
			g.softerThan = value.at(firstVal) == '<';
			g.values = std::make_pair(std::stoi(value.substr(0, firstVal)), std::stoi(value.substr(firstVal + 1, value.size())));
			return g;
		}) | std::ranges::to<std::vector>();
	}
	);
	std::println("problem 2026, q2, p3:");
	u64 accum = 0;
	for (const auto& line : problem) {
		u32 lineAccum = 0;
		auto map = Quest2::Internal::harderMap(line);
		Quest2::Internal::refineHarderMap(map);
		std::vector<u32> ordered{};
		ordered.reserve(map.size());
		for (const auto [k, v] : map) {
			ordered.emplace_back(k);
		}
		std::sort(ordered.begin(), ordered.end(), [&map](const u32 a, const u32 b) -> bool {
			const auto& aSet = map.at(a);
			const auto& bSet = map.at(b);
			if (aSet.contains(b)) return true;
			else if (bSet.contains(a)) return false;
			std::unreachable();
		});
		for (const auto v : ordered) {
			lineAccum = (lineAccum * 10) + v;
		}
#ifdef _DEBUG
		std::println("lineAccum: {}", lineAccum);
#endif
		accum += lineAccum;
	}
	std::println("\ttime p3: {}", t.getElapsedSinceConstruction());
	return accum;
}

auto Quest2::Internal::harderFrequency(const std::vector<Quest2::Internal::Group>& groups) -> std::map<u32, u32> {
	const auto freq = Quest2::Internal::unorderedHarderFrequency(groups);
	std::map<u32, u32> order{};
	for (auto& [k, v] : freq) {
		order.emplace(v, k); // works so long as there's no hardness ties. otherwise overwrites.
	}
	return order;
}

auto Quest2::Internal::unorderedHarderFrequency(const std::vector<Quest2::Internal::Group>& groups) -> std::unordered_map<u32, u32> {
	std::unordered_map<u32, u32> freq{};
	for (const auto& group : groups) {
		if (freq.find(group.values.first) == freq.end()) {
			freq.emplace(group.values.first, 0);
		}
		if (freq.find(group.values.second) == freq.end()) {
			freq.emplace(group.values.second, 0);
		}
		freq.at(group.softerThan ? group.values.first : group.values.second) += 1;
	}
	return freq;
}

auto Quest2::Internal::harderMap(const std::vector<Quest2::Internal::Group>& groups) -> std::unordered_map<u32, std::set<u32>> {
	std::unordered_map<u32, std::set<u32>> freq{};
	for (const auto& group : groups) {
		if (freq.find(group.values.first) == freq.end()) {
			freq.emplace(group.values.first, std::set<u32>{});
		}
		if (freq.find(group.values.second) == freq.end()) {
			freq.emplace(group.values.second, std::set<u32>{});
		}
		freq.at(group.softerThan
			? group.values.second
			: group.values.first
		).insert(group.softerThan
			? group.values.first
			: group.values.second
		);
	}
	return freq;
}

// overkill for p2 (only 2 of the keys will have the same length. one of those is missing a rule)
auto Quest2::Internal::refineHarderMap(std::unordered_map<u32, std::set<u32>>& values) -> void {
	for (auto& [k, v] : values) {
		for (const auto& wasHarderThan : v) {
			v.insert_range(values[wasHarderThan]);
		}
	}
}
