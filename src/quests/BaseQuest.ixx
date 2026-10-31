
export module BaseQuest;

import Utils;

import <string>;
import <expected>;
import <exception>;
import <array>;
import <utility>;

export {
	class QuestUnimplemented : public std::exception {
		virtual auto what() const noexcept -> const char* override {
			return "UNIMPLEMENTED";
		}
	};

	class ParsedQuestStrings {
	protected:
		std::string _parsed1;
		std::string _parsed2;
		std::string _parsed3;

	public:
		ParsedQuestStrings(u32, u32);
	};

	template <typename S1, typename S2 = S1, typename S3 = S1>
	struct BaseQuest : public ParsedQuestStrings {
		BaseQuest(u32 year, u32 quest) : ParsedQuestStrings{ year, quest } {}

		auto [[nodiscard]] timeSolutions() const noexcept -> std::array<std::string, 3> {
			std::array<std::string, 3> results{};
			Timer::Timer t{};
			const auto res1 = this->solution1(this->_parsed1);
			results[0] = t.getElapsedSinceLastSet();
			t.set();
			const auto res2 = this->solution2(this->_parsed2);
			results[1] = t.getElapsedSinceLastSet();
			t.set();
			const auto res3 = this->solution3(this->_parsed3);
			results[2] = t.getElapsedSinceLastSet();
			if (!res1.has_value()) {
				results[0] = "";
			}
			if (!res2.has_value()) {
				results[1] = "";
			}
			if (!res3.has_value()) {
				results[2] = "";
			}
			return results;
		}
		auto [[nodiscard]] getSolutions() const noexcept -> std::tuple<S1, S2, S3> {
			std::tuple<S1, S2, S3> solutions{}; // prob requires S1-3 are default constructable
			const auto& res1 = this->solution1(this->_parsed1);
			if (res1.has_value()) {
				std::get<0>(solutions) = res1.value();
			}
			const auto& res2 = this->solution2(this->_parsed2);
			if (res2.has_value()) {
				std::get<1>(solutions) = res2.value();
			}
			const auto& res3 = this->solution3(this->_parsed3);
			if (res3.has_value()) {
				std::get<2>(solutions) = res3.value();
			}
			return solutions;
		}

	protected:
		virtual auto [[nodiscard]] solution1(const std::string&) const noexcept -> std::expected<S1, QuestUnimplemented> = 0;
		virtual auto [[nodiscard]] solution2(const std::string&) const noexcept -> std::expected<S2, QuestUnimplemented> = 0;
		virtual auto [[nodiscard]] solution3(const std::string&) const noexcept -> std::expected<S3, QuestUnimplemented> = 0;
	};
}
