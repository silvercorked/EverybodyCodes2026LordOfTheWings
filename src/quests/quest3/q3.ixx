
export module Quest3;

import Utils;
import BaseQuest;

import <vector>;
import <array>;

namespace Q3Helpers {
	struct Vote {
		u64 standard;
		u64 encodedVote;

		Vote(u64, u64);
	};
	auto [[nodiscard]] getAtPosFromBase(u64, size_t, u64 = 10) -> std::pair<u64, bool>;
	auto [[nodiscard]] isMin(u64, u64, u64) -> bool;
	auto [[nodiscard]] getVote(u64, u64) -> u64;
};

export
struct Quest3 : public BaseQuest<u32, u64, u64> {
	Quest3();

protected:
	auto [[nodiscard]] solution1(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> final;
	auto [[nodiscard]] solution2(const std::string&) const noexcept -> std::expected<u64, QuestUnimplemented> final;
	auto [[nodiscard]] solution3(const std::string&) const noexcept -> std::expected<u64, QuestUnimplemented> final;

private:
	// static auto [[nodiscard]] parse(const std::string&) noexcept -> std::vector<Q3Helpers::Vote>;
};
