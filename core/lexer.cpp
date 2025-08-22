#include "lexer.hpp"
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <cstdlib>

std::vector<token> tokenize(std::string& src) {
    std::istringstream iss(src);
    std::vector<token> tokens {};
    std::string word;

    while (iss >> word) {
        if (!word.compare("push")) {
            tokens.push_back({ token_t::PUSH, "" });
        } else if (!word.compare("pop")) {
            tokens.push_back({ token_t::POP, "" });
        } else if (!word.compare("store")) {
            tokens.push_back({ token_t::STORE, "" });
        } else if (!word.compare("load")) {
            tokens.push_back({ token_t::LOAD, "" });
        } else if (!word.compare("swap")) {
            tokens.push_back({ token_t::SWAP, "" });
        } else if (!word.compare("dup")) {
            tokens.push_back({ token_t::DUP, "" });
        } else if (!word.compare("call")) {
            tokens.push_back({ token_t::CALL, "" });
        } else if (!word.compare("callf")) {
            tokens.push_back({ token_t::CALLF, "" });
        } else if (word.back() == ':') {
            tokens.push_back({ token_t::LABEL, word.substr(0, word.size()-1) });
        } else if (std::all_of(word.begin(), word.end(), ::isalpha)) {
            tokens.push_back({ token_t::IDENT, word });
        } else if (std::all_of(word.begin(), word.end(), ::isxdigit)) {
            tokens.push_back({ token_t::NUMBER, word });
        } else if (!word.compare("clear")) {
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
            continue;
        } else {
            std::cerr << "Unexpected token: " << word << '\n';
            std::exit(1);
        }
    }

    tokens.push_back({ token_t::END, "" });
    return tokens;
}
