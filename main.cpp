#include "core/lexer.hpp"
#include "core/ir.hpp"
#include "core/interpreter.hpp"
#include "core/vm.hpp"
#include "core/builtin.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

std::string readfile(std::string pat);

/*TODO:
 * uppercase/lowercase string
 * stacksize (size or bytes)
 * skibidi (skibidi "soundtrack" loop)
 * libmr.a (yeah, my own lib for my own OS)
 * */

int main(void) {
	struct MrLangVM vm;
	std::string code;
	std::vector<token> tokens;
	std::vector<instruction> instructions;
	code = readfile("index.mr");
	tokens = tokenize(code);
	instructions = translateIR(tokens);
	
	MrLang_initbuiltin(&vm);
	run_program(&vm, instructions);

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
