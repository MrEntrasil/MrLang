#pragma once
#include <string>
#include <vector>
#include "lexer.hpp"

enum class opcode {
    PUSH_STR, PUSH_NUM,
    CLEARSTACK, POP,
    END, STORE,
    LOAD, IDENT
};

struct instruction {
    opcode op;
    std::string operand;
};

void push_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir);
void store_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir);
void load_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir);

std::vector<instruction> translateIR(std::vector<token> tokens);
