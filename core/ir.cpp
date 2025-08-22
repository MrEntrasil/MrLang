#include "ir.hpp"
#include <iostream>
#include <cstdlib>

std::vector<instruction> translateIR(std::vector<token> tokens) {
    std::vector<instruction> ir {};
    for (size_t i = 0; i < tokens.size(); i++) {
        token t = tokens[i];

        switch (t.type) {
            case token_t::STORE:
                store_key(&tokens, &i, &ir);
                break;
            case token_t::PUSH:
                push_key(&tokens, &i, &ir);
                break;
            case token_t::LOAD:
                load_key(&tokens, &i, &ir);
                break;
            case token_t::POP:
                ir.push_back({ opcode::POP, "" });
                break;
            case token_t::CLEARSTACK:
                ir.push_back({ opcode::CLEARSTACK,"" });
                break;
            case token_t::DUP:
                ir.push_back({ opcode::DUP, "" });
                break;
            case token_t::SWAP:
                ir.push_back({ opcode::SWAP, "" });
                break;
            case token_t::END:
                ir.push_back({ opcode::END, "" });
                break;
            case token_t::IDENT:
                ir.push_back({ opcode::IDENT, t.value });
                break;
            default:
                break;
        }
    }

    return ir;
}

void push_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir) {
    if (tokens->size() > *i + 1) {
        if (tokens->at(*i+1).type == token_t::NUMBER) {
            ir->push_back({ opcode::PUSH_NUM, tokens->at(*i+1).value });
            (*i)++;
        } else if (tokens->at(*i+1).type == token_t::STRING) {
            ir->push_back({ opcode::PUSH_STR, tokens->at(*i+1).value });
            (*i)++;
        } else {
            std::cerr << "IR error: push has no value!\n";
            std::exit(1);
        }
    } else {
        std::cerr << "IR error: push has no value!\n";
        std::exit(1);
    }
}

void store_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir) {
    if (tokens->size() > *i + 1 && tokens->at(*i+1).type == token_t::IDENT) {
        ir->push_back({ opcode::STORE, tokens->at(*i+1).value });
        (*i)++;
    } else {
        std::cerr << "IR error: 'store' has no value or value isn't an identifier\n";
        std::exit(1);
    }
}

void load_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir) {
    if (tokens->size() > *i + 1 && tokens->at(*i+1).type == token_t::IDENT) {
        ir->push_back({ opcode::LOAD, tokens->at(*i+1).value });
        (*i)++;
    } else {
        std::cerr << "IR error: 'load' has no value or value isn't an identifier\n";
        std::exit(1);
    }
}
