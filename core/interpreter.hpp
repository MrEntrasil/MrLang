#pragma once
#include <vector>
#include <iostream>
#include <variant>
#include "ir.hpp"

using anypp = std::variant<int32_t, std::string>;

void run_program(std::vector<instruction> ir) {
	std::vector<anypp> st {};

	for (size_t i = 0;i < ir.size();i++) {
		instruction instr = ir[i];

		switch (instr.op) {
			case opcode::PUSH_STR:
				st.push_back(instr.operand);
				break;
			case opcode::PUSH_NUM:
				st.push_back(instr.operand);
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
			default: break;
		}
	}
}
