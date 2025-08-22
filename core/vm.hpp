#pragma once
#include <string>
#include <vector>
#include <variant>
#include <unordered_map>
#include <functional>

struct MrLangVM {
		std::unordered_map<std::string, std::variant<std::string, int>> vars;
	std::vector<std::variant<std::string, int>> st;
	std::unordered_map<std::string, std::function<void(struct MrLangVM*)>> funcs;
};
