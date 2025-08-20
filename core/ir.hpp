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
	END,
	ADD, SUB,
	DIV, MUL,
	STORE, LOAD
};

struct instruction {
	opcode op;
	std::string operand;
};

void push_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir);
void store_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir);
void load_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir);

std::vector<instruction> translateIR(std::vector<token> tokens) {
	std::vector<instruction> ir {};
	for (size_t i = 0;i < tokens.size();i++) {
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
			case token_t::ADD:
				ir.push_back({ opcode::ADD, "" });
				break;
			case token_t::SUB:
				ir.push_back({ opcode::SUB, "" });
				break;
			case token_t::MUL:
				ir.push_back({ opcode::MUL, "" });
				break;
			case token_t::DIV:
				ir.push_back({ opcode::DIV, "" });
				break;
			default: break;
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
		std::cerr << "IR error: 'store' has no value or value is'nt an indentifier\n";
		std::exit(1);
	}
}

void load_key(std::vector<token>* tokens, size_t* i, std::vector<instruction>* ir) {
	if (tokens->size() > *i + 1 && tokens->at(*i+1).type == token_t::IDENT) {
		ir->push_back({ opcode::LOAD, tokens->at(*i+1).value });
		(*i)++;
	} else {
		std::cerr << "IR error: 'load' has no value or value is'nt an identifier\n";
		std::exit(1);
	}
}
