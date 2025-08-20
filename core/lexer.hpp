#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

enum class token_t {
	END, NUMBER, STRING,
	IDENT,

	PUSH, POP, PRINT,
	CLEARSTACK, ADD, SUB,
	DIV, MUL, STORE,
	LOAD
};

struct token {
	token_t type;
	std::string value;
};

std::vector<token> tokenize(std::string& src) {
	std::istringstream iss(src);
	std::vector<token> tokens {};
	std::string word;

	while (iss >> word) {
			if (!word.compare("push")) {
				tokens.push_back({ token_t::PUSH, "" });
			} else if (!word.compare("pop")) {
				tokens.push_back({ token_t::POP, "" });
			} else if (!word.compare("print")) {
				tokens.push_back({ token_t::PRINT, "" });
			} else if (!word.compare("add")) {
				tokens.push_back({ token_t::ADD, "" });
			} else if (!word.compare("sub")) {
				tokens.push_back({ token_t::SUB, "" });
			} else if (!word.compare("div")) {
				tokens.push_back({ token_t::DIV, "" });
			} else if (!word.compare("mul")) {
				tokens.push_back({ token_t::MUL, "" });
			} else if (!word.compare("store")) {
				tokens.push_back({ token_t::STORE, "" });
			} else if (!word.compare("load")) {
				tokens.push_back({ token_t::LOAD, "" });
			} else if (std::all_of(word.begin(), word.end(), ::isalpha)) {
				tokens.push_back({ token_t::IDENT, word });
			} else if (std::all_of(word.begin(), word.end(), ::isdigit)) {
				tokens.push_back({ token_t::NUMBER, word });
			} else if (!word.compare("clear_stack")) {
				tokens.push_back({ token_t::CLEARSTACK, "" });
			} else if (word.front() == '"') {
				std::string str = word.substr(1);
				bool done = false;

				while (!done) {
					if (!str.empty() && str.back() == '"') {
						str.pop_back();
						done = true;
					} else if (iss >> word) {
						str += " " + word;
					} else {
						std::cerr << "Lexical error: unterminated string literal\n";
						std::exit(1);
					}
				}
				tokens.push_back({ token_t::STRING, str });
			} else if (word == "//") {
				std::string buff;
				std::getline(iss, buff);
				buff.clear();
				continue;
			} else {
				std::cerr << "Unexpected token: " << word << '\n';
				std::exit(1);
			}
	}

	tokens.push_back({ token_t::END, "" });
	return tokens;
}
