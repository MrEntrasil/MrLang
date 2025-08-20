#include <iostream>
#include <string>
#include <fstream>
#include "core/lexer.hpp"
#include "core/ir.hpp"
#include "core/interpreter.hpp"

std::string readfile(std::string pat);

int main(void) {
	std::string code;
	std::vector<token> tokens;
	std::vector<instruction> instructions;
	code = readfile("index.mr");
	tokens = tokenize(code);
	instructions = translateIR(tokens);

	run_program(instructions);

	return EXIT_SUCCESS;
}

std::string readfile(std::string pat) {
	std::ostringstream oss;
	std::ifstream file(pat);
	if (!file.is_open()) {
		std::cerr << "Could not open: " << pat << '\n';
		std::exit(1);
	}
	oss << file.rdbuf();
	file.close();

	return oss.str();
}
