#pragma once
#include <string>
#include <vector>

enum class token_t {
    END, NUMBER, STRING,
    IDENT,
    PUSH, POP, CLEARSTACK,
    STORE, LOAD
};

struct token {
    token_t type;
    std::string value;
};

std::vector<token> tokenize(std::string& src);
