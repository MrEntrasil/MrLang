#include "vm.hpp"
#include <iostream>

bool MrLang_NewFunction(MrLangVM* vm, std::string funcname, MrLang_Function fn) {
	if (vm->funcs.count(funcname)) {
		return false;
	}
	vm->funcs[funcname] = fn;

	return true;
}
