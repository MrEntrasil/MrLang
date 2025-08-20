#pragma once
#include <iostream>
#include <vector>
#include "lexer.hpp"

enum class opcode {
	PUSH_STR,
	PUSH_NUM,
	PRINT,
	CLEARSTACK,
	POP,
	END
};

struct instruction {
	opcode op;
	std::string operand;
};

std::vector<instruction> translateIR(std::vector<token> tokens) {
	std::vector<instruction> ir {};
	for (size_t i = 0;i < tokens.size();i++) {
		token t = tokens[i];
		
		switch (t.type) {
			case token_t::PUSH:
				if (tokens.size() > i + 1) {
					if (tokens[i+1].type == token_t::NUMBER) {
						ir.push_back({ opcode::PUSH_NUM, tokens[i+1].value });
						i++;
					} else if (tokens[i+1].type == token_t::STRING) {
						ir.push_back({ opcode::PUSH_STR, tokens[i+1].value });
						i++;
					} else {
						std::cerr << "IR error: push has no value!\n";
						std::exit(1);
					}
				} else {
					std::cerr << "IR error: push has no value!\n";
					std::exit(1);
				}
				break;
			case token_t::PRINT:
				ir.push_back({ opcode::PRINT, "" });
				break;
			case token_t::POP:
				ir.push_back({ opcode::POP, "" });
				break;
			case token_t::CLEARSTACK:
				ir.push_back({ opcode::CLEARSTACK,"" });
				break;
			case token_t::END:
				ir.push_back({ opcode::END, "" });
				break;
			default: break;
		}
	}

	return ir;
}
