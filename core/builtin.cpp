#include "builtin.hpp"
#include "error.hpp"
#include <string>
#include <iostream>

void MrLang_initbuiltin(struct MrLangVM* vm){
	vm->funcs["print"] = [](struct MrLangVM* vm) {
		if (vm->st.empty()) {
			std::cout << "print error: stack is empty\n";
			std::exit(1);
		}

		std::visit([](auto& val){
			std::cout << val << '\n';
		}, vm->st.back());
	};

	vm->funcs["add"] = [](struct MrLangVM* vm){
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
	};

	vm->funcs["sub"] = [](struct MrLangVM* vm){
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
	};

	vm->funcs["mul"] = [](struct MrLangVM* vm){
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
	};

	vm->funcs["div"] = [](struct MrLangVM* vm){
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
	};
}
