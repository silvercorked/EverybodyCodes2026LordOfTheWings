
module Quest3;

Quest3::Quest3() : BaseQuest{ 2026, 3 } {}

auto [[nodiscard]] Quest3::solution1(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> {
	return std::unexpected(QuestUnimplemented{});
}
auto [[nodiscard]] Quest3::solution2(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> {
	return std::unexpected(QuestUnimplemented{});
}
auto [[nodiscard]] Quest3::solution3(const std::string&) const noexcept -> std::expected<u32, QuestUnimplemented> {
	return std::unexpected(QuestUnimplemented{});
}
