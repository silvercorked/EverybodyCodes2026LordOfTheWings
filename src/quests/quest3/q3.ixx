
export module Quest3;

import Utils;
import BaseQuest;

export
struct Quest3 : public BaseQuest<u32> {
	Quest3();

protected:
	auto [[nodiscard]] solution1(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> final;
	auto [[nodiscard]] solution2(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> final;
	auto [[nodiscard]] solution3(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> final;
};
