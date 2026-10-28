
#include "FileReadUtils.hpp"

#include <fstream>
#include <sstream>
#include <expected>
#include <filesystem>
#include <string>
#include <ranges>
#include <stdexcept>

auto [[nodiscard]] FileReadUtils::readFile(const std::filesystem::path& path) -> std::expected<std::string, std::string> {
	std::ifstream file(path.c_str());
	if (!file.is_open()) {
		return std::unexpected("Unable to open file");
	}

	std::stringstream ss;
	ss << file.rdbuf();
	file.close();
	return ss.str();
}

auto [[nodiscard]] FileReadUtils::readFileCSL(const std::filesystem::path& path) -> std::expected<std::vector<std::string>, std::string> {
	auto fileOut = readFile(path);
	if (fileOut.has_value()) {
		return parseFileCSL(fileOut.value());
	}
	return std::unexpected(fileOut.error());
}

auto [[nodiscard]] FileReadUtils::readFileCSV(const std::filesystem::path& path) -> std::expected<std::vector<std::vector<std::string>>, std::string> {
	auto fileOut = readFile(path);
	if (fileOut.has_value()) {
		return parseFileCSV(fileOut.value());
	}
	return std::unexpected(fileOut.error());
}

auto [[nodiscard]] FileReadUtils::readProblemFile(u32 year, u32 quest, u32 part) -> std::string {
	const auto problem = readFile(std::format("data/everybody_codes_e{}_q{:02d}_p{}.txt", year, quest, part));
	if (problem.has_value()) {
		return problem.value();
	}
	throw std::runtime_error(problem.error());
}

auto [[nodiscard]] FileReadUtils::parseFileCSL(std::string_view fileContents, std::string_view delim) -> std::vector<std::string> {
	std::vector<std::string> out{};
	for (const auto& value : fileContents | std::ranges::views::split(delim)) {
		out.emplace_back(std::string_view(value));
	}
	return out;
}
auto [[nodiscard]] FileReadUtils::parseFileCSV(std::string_view fileContents, std::string_view delimValue, std::string_view delimLine) -> std::vector<std::vector<std::string>> {
	std::vector<std::vector<std::string>> out{};
	for (const auto& line : fileContents | std::ranges::views::split(delimLine)) {
		out.emplace_back();
		for (const auto& value : line | std::ranges::views::split(delimValue)) {
			out.back().emplace_back(std::string_view(value));
		}
	}
	return out;
}

