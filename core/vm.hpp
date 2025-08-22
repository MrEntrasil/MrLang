#pragma once
#include <string>
#include <vector>
#include <variant>
#include <unordered_map>
#include <functional>

using MrLang_Function = std::function<void(struct MrLangVM*)>;

struct MrLangVM {
	std::unordered_map<std::string, std::variant<std::string, int>> vars;
	std::vector<std::variant<std::string, int>> st;
	std::unordered_map<std::string, MrLang_Function> funcs;
	std::unordered_map<std::string, size_t> labels;
};

bool MrLang_NewFunction(MrLangVM* vm, std::string funcname, MrLang_Function fn);
