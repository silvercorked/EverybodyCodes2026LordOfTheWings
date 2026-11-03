
module Quest2;

import Utils;

#ifdef _DEBUG
import <print>;
#endif

import <ranges>;
import <string>;
import <algorithm>;

using namespace FileReadUtils;

Quest2::Quest2() : BaseQuest{ 2026, 2 } {}

auto Q2Helpers::harderFrequency(const std::vector<Q2Helpers::Group>& groups) -> std::map<u32, u32> {
	const auto freq = Q2Helpers::unorderedHarderFrequency(groups);
	std::map<u32, u32> order{};
	for (auto& [k, v] : freq) {
		order.emplace(v, k); // works so long as there's no hardness ties. otherwise overwrites.
	}
	return order;
}

auto Q2Helpers::unorderedHarderFrequency(const std::vector<Q2Helpers::Group>& groups) -> std::unordered_map<u32, u32> {
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

auto Q2Helpers::harderMap(const std::vector<Q2Helpers::Group>& groups) -> std::unordered_map<u32, std::set<u32>> {
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
auto Q2Helpers::refineHarderMap(std::unordered_map<u32, std::set<u32>>& values) -> void {
	for (auto& [k, v] : values) {
		for (const auto& wasHarderThan : v) {
			v.insert_range(values[wasHarderThan]);
		}
	}
}

auto [[nodiscard]] Quest2::solution1(const std::string& p) const noexcept -> std::expected<u32, QuestUnimplemented> {
	auto problem = Quest2::parse(p);
#ifdef _DEBUG
	std::println("problem 2026, q2, p1:");
#endif
	u32 accum = 0;
	for (const auto& line : problem) {
		u32 lineAccum = 0;
		auto orderedMap = Q2Helpers::harderFrequency(line);
		for (const auto [k, v] : orderedMap) {
			lineAccum = (lineAccum * 10) + v;
		}
#ifdef _DEBUG
		std::println("lineAccum: {}", lineAccum);
#endif
		accum += lineAccum;
	}
	return accum;
}

auto [[nodiscard]] Quest2::solution2(const std::string& p) const noexcept -> std::expected<u64, QuestUnimplemented> {
	auto problem = Quest2::parse(p);
#ifdef _DEBUG
	std::println("problem 2026, q2, p2:");
#endif
	u64 accum = 0;
	for (const auto& line : problem) {
		u32 lineAccum = 0;
		auto map = Q2Helpers::harderMap(line);
		Q2Helpers::refineHarderMap(map);
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
	return accum;
}

auto [[nodiscard]] Quest2::solution3(const std::string& p) const noexcept -> std::expected<u64, QuestUnimplemented> { // this is the same as p2 but the p3 file
	auto problem = Quest2::parse(p);
#ifdef _DEBUG
	std::println("problem 2026, q2, p3:");
#endif
	u64 accum = 0;
	for (const auto& line : problem) {
		u32 lineAccum = 0;
		auto map = Q2Helpers::harderMap(line);
		Q2Helpers::refineHarderMap(map);
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
	return accum;
}

auto [[nodiscard]] Quest2::parse(const std::string& p) noexcept -> std::vector<std::vector<Q2Helpers::Group>> {
	return parseFileCSV(p, " ") | std::ranges::views::transform(
		[](const std::vector<std::string>& line) -> std::vector<Q2Helpers::Group> {
			return line | std::ranges::views::transform([](const std::string& value) -> Q2Helpers::Group {
				u32 firstVal = 0;
				char curr = value.at(firstVal);
				while (curr != '<' && curr != '>') {
					++firstVal;
					curr = value.at(firstVal);
				}
				Q2Helpers::Group g{};
				g.softerThan = value.at(firstVal) == '<';
				g.values = std::make_pair(std::stoi(value.substr(0, firstVal)), std::stoi(value.substr(firstVal + 1, value.size())));
				return g;
			}) | std::ranges::to<std::vector>();
		}
	) | std::ranges::to<std::vector>();
}
