#pragma once
#include <vector>
#include <iostream>
#include <variant>
#include <unordered_map>
#include "ir.hpp"

using anypp = std::variant<int32_t,std::string>;

void run_program(std::vector<instruction> ir) {
	std::vector<anypp> st {};
	std::unordered_map<std::string,anypp> vars {};

	for (size_t i = 0;i < ir.size();i++) {
		instruction instr = ir[i];

		switch (instr.op) {
			case opcode::PUSH_STR:
				st.push_back(instr.operand);
				break;
			case opcode::PUSH_NUM:
				st.push_back(std::stoi(instr.operand));
				break;
			case opcode::POP:
				if (!st.empty()) {
					st.pop_back();
				} else {
					std::cerr << "interpreter error: stack is empty\n";
					std::exit(1);
				}
				break;
			case opcode::PRINT:
				if (!st.empty()) {
					std::visit([](auto&& val){
						std::cout << val << '\n';
					}, st.back());
				} else {
					std::cerr << "interpreter error: stack is empty\n";
					std::exit(1);
				}
				break;
			case opcode::CLEARSTACK:
				st.clear();
				break;
			case opcode::END:
				return;
			case opcode::STORE:
				if (!st.empty()) {
					vars[instr.operand] = st.back();
					st.pop_back();
				} else {
					std::cerr << "interpreter error: stack is empty!\n";
					std::exit(1);
				}
				break;
			case opcode::LOAD: {
				auto val = vars.find(instr.operand);
				if (val != vars.end()) {
					st.push_back(val->second);
					vars.erase(val);
				} else {
					std::cout << "interpreter error: variable '" << instr.operand << "' not found!\n";
					std::exit(1);
				}
				break;
			}
			case opcode::SUB:
			case opcode::DIV:
			case opcode::MUL:
			case opcode::ADD: {
				if (st.size() < 2) {
					std::cerr << "interpreter error: arithmetic operations require at least 2 values on the stack\n";
					std::exit(1);
				}
				auto a = st.back();
				st.pop_back();
				auto b = st.back();
				st.pop_back();
				
				if (std::holds_alternative<int>(a) && std::holds_alternative<int>(b)) {
					int x = std::get<int>(b);
					int y = std::get<int>(a);
					
					switch (instr.op) {
						case opcode::ADD:
							st.push_back(x+y);
							break;
						case opcode::SUB:
							st.push_back(x-y);
							break;
						case opcode::DIV:
							st.push_back(x/y);
							break;
						case opcode::MUL:
							st.push_back(x*y);
							break;
						default: break;
					}
				} else {
					std::cerr << "interpreter error: arithmetic operations only work with numbers\n";
					std::exit(1);
				}
			}
			default: break;
		}
	}
}
