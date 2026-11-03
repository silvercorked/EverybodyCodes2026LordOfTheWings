
module Quest3;

import Utils;

import <ranges>;
import <numeric>;
import <algorithm>;
import <cmath>;
import <vector>;

#ifdef _DEBUG
import <print>;
#endif

Q3Helpers::Vote::Vote(u64 _a, u64 _b) : standard{ _a }, encodedVote{ _b } {}

auto [[nodiscard]] Q3Helpers::getVote(u64 standard, u64 encodedVote) -> u64 {
	size_t max1Index = 0;
	u64 accum = 0;
	for (size_t i = 0; true; ++i) {
		u64 s, e;
		bool sHasMore, eHasMore;
		std::tie(s, sHasMore) = Q3Helpers::getAtPosFromBase(standard, max1Index ? i % max1Index : i);
		std::tie(e, eHasMore) = Q3Helpers::getAtPosFromBase(encodedVote, i);
		if (!eHasMore) {
			break;
		}
		if (!sHasMore) {
			max1Index = i;
			s = Q3Helpers::getAtPosFromBase(standard, i % max1Index).first;
		}
		accum += static_cast<u64>(std::pow(s, i)) * e;
	}
	return accum;
}

auto [[nodiscard]] Q3Helpers::getAtPosFromBase(u64 num, size_t pos, u64 base) -> std::pair<u64, bool> {
	for (; pos; --pos) {
		num /= base;
	}
	return std::make_pair<u64, bool>(num % base, static_cast<bool>(num));
}

auto [[nodiscard]] Q3Helpers::isMin(u64 vote, u64 standard, u64 encodedVote) -> bool {
	for (u64 candidate = 0; candidate < encodedVote; ++candidate) {
		if (getVote(standard, candidate) == vote) {
			return false;
		}
	}
	return true;
}

Quest3::Quest3() : BaseQuest{ 2026, 3 } {}

auto [[nodiscard]] Quest3::solution1(const std::string& p) const noexcept -> std::expected<u32, QuestUnimplemented> {
	const auto asNums = FileReadUtils::parseFileCSL(p, "\n") | std::ranges::views::transform([](std::string& p) -> u32 {
		const u32 index = 4;
		const u32 offset = 5;
		const u32 numSize = 4;
		u32 accum = 0;
		for (auto i = 0; i < numSize; ++i) {
			const u32 num1 = static_cast<u32>(p.at(index + i) - 0x30);
			const u32 num2 = static_cast<u32>(p.at(index + offset + i) - 0x30);
			accum += static_cast<u32>(std::pow(num1, numSize - (i + 1))) * num2;
		}
		return accum;
	}) | std::ranges::to<std::vector>();
	return std::ranges::fold_left(asNums, 0, std::plus{});
}
auto [[nodiscard]] Quest3::solution2(const std::string& p) const noexcept -> std::expected<u64, QuestUnimplemented> {
	const auto votes = FileReadUtils::parseFileCSL(p, "\n");
	u64 accum = 0;
	for (const auto& vote : votes) {
		const size_t n1IndexStart = vote.find(' ') - 1;
		const size_t n2IndexStart = vote.size() - 1;
		const size_t n1Len = n1IndexStart - 3;
		const size_t n2Len = n2IndexStart - (n1IndexStart + 1);
		bool expand1 = false;
		bool expand2 = false;
		for (size_t i = 0; !expand2; ++i) {
			u8 num1 = 0;
			u8 num2 = 0;
			if (expand1) {
				num1 = vote.at(n1IndexStart - (i % n1Len)) - 0x30;
			}
			else {
				num1 = vote.at(n1IndexStart - i) - 0x30;
				if (i == n1Len - 1) {
					expand1 = true;
				}
			}
			// if (expand2) {
			// 	num2 = vote.at(n2IndexStart - (i % n2Len)) - 0x30;
			// }
			// else {
				num2 = vote.at(n2IndexStart - i) - 0x30;
				if (i == n2Len - 1) {
					expand2 = true;
				}
			// }
#ifdef _DEBUG
			std::println("{}^{} = {}, * {} = {}, accum = {}", num1, i, static_cast<u64>(std::pow(num1, i)), static_cast<u64>(num2), static_cast<u64>(std::pow(num1, i)) * static_cast<u64>(num2), accum + static_cast<u64>(std::pow(num1, i)) * static_cast<u64>(num2));
#endif
			accum += static_cast<u64>(std::pow(num1, i)) * static_cast<u64>(num2);
		}
	}
	return accum;
}
auto [[nodiscard]] Quest3::solution3(const std::string& p) const noexcept -> std::expected<u64, QuestUnimplemented> {
	const auto votes = FileReadUtils::parseFileCSL(p, "\n");
	u64 accum = 0;
	for (const auto& vote : votes) {
		constexpr const size_t n1IndexStart = 5;
		const size_t n2IndexStart = vote.find(' ', n1IndexStart) + 1;
		u64 standard = std::stoul(vote.substr(n1IndexStart));
		u64 encodedVote = std::stoul(vote.substr(n2IndexStart));
		const u64 candidate = Q3Helpers::getVote(standard, encodedVote);
		const bool wasMin = Q3Helpers::isMin(candidate, standard, encodedVote);
#ifdef _DEBUG
		std::println("s: {}, e: {}, candidate: {}, wasMin: {}", standard, encodedVote, candidate, wasMin);
#endif
		if (wasMin) {
			accum += candidate;
		}
	}
	return accum;
}
