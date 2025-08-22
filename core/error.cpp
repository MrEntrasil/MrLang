#include "error.hpp"
#include <iostream>

void MrLangError_stacksize(size_t s, std::string funcname) {
	std::cout << funcname << " error: stack needs at least " << s << " contents in stack!\n";
	std::exit(1);
}

void MrLangError_wrongtype(std::string expected_type, std::string funcname) {
	std::cout << funcname << " error: expected type " << expected_type << '\n';
	std::exit(1);
}
