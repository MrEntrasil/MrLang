#include "builtin.hpp"
#include "error.hpp"
#include <string>
#include <iostream>

void MrLang_initbuiltin(struct MrLangVM* vm){
	MrLang_NewFunction(vm, "print", [](struct MrLangVM* vm) {
		if (vm->st.empty()) {
			std::cout << "print error: stack is empty\n";
			std::exit(1);
		}

		std::visit([](auto& val){
			std::cout << val << '\n';
		}, vm->st.back());
	});

	MrLang_NewFunction(vm, "add", [](struct MrLangVM* vm){
		if (vm->st.size() < 2) MrLangError_stacksize(2, "add");
		auto a = vm->st.back();
		vm->st.pop_back();
		auto b = vm->st.back();
		vm->st.pop_back();
		
		if (std::holds_alternative<int>(a) && std::holds_alternative<int>(b)) {
			int x = std::get<int>(b);
			int y = std::get<int>(a);

			vm->st.push_back(x+y);
		} else MrLangError_wrongtype("number", "add");
	});

	MrLang_NewFunction(vm, "sub", [](struct MrLangVM* vm){
		if (vm->st.size() < 2) MrLangError_stacksize(2, "sub");
		auto a = vm->st.back();
		vm->st.pop_back();
		auto b = vm->st.back();
		vm->st.pop_back();

		if (std::holds_alternative<int>(a) && std::holds_alternative<int>(b)) {
			int x = std::get<int>(b);
			int y = std::get<int>(a);

			vm->st.push_back(x-y);
		} else MrLangError_wrongtype("number", "sub");
	});

	MrLang_NewFunction(vm, "mul", [](struct MrLangVM* vm){
		if (vm->st.size() < 2) MrLangError_stacksize(2, "mul");
		auto a = vm->st.back();
		vm->st.pop_back();
		auto b = vm->st.back();
		vm->st.pop_back();

		if (std::holds_alternative<int>(a) && std::holds_alternative<int>(b)) {
			int x = std::get<int>(b);
			int y = std::get<int>(a);

			vm->st.push_back(x*y);
		} else MrLangError_wrongtype("number", "mul");
	});

	MrLang_NewFunction(vm, "div", [](struct MrLangVM* vm){
		if (vm->st.size() < 2) MrLangError_stacksize(2, "div");
		auto a = vm->st.back();
		vm->st.pop_back();
		auto b = vm->st.back();
		vm->st.pop_back();

		if (std::holds_alternative<int>(a) && std::holds_alternative<int>(b)) {
			int x = std::get<int>(b);
			int y = std::get<int>(a);

			vm->st.push_back(x/y);
		} else MrLangError_wrongtype("number", "div");
	});
}
