#pragma once

#include "PrimitiveTypes.hpp"

#include <filesystem>
#include <expected>
#include <string>
#include <vector>

namespace FileReadUtils {
	auto [[nodiscard]] readFile(const std::filesystem::path& path) -> std::expected<std::string, std::string>;
	// comma-seperated list, csv but no newlines
	auto [[nodiscard]] readFileCSL(const std::filesystem::path& path) -> std::expected<std::vector<std::string>, std::string>;
	auto [[nodiscard]] readFileCSV(const std::filesystem::path& path) -> std::expected<std::vector<std::vector<std::string>>, std::string>;

	auto [[nodiscard]] readProblemFile(u32 year, u32 quest, u32 part) -> std::string;
	// comma-seperated list, csv but no newlines
	auto [[nodiscard]] parseFileCSL(std::string_view fileContents, std::string_view = ",") -> std::vector<std::string>;
	auto [[nodiscard]] parseFileCSV(std::string_view fileContents, std::string_view = ",", std::string_view = "\n")->std::vector<std::vector<std::string>>;
}