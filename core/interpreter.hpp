#pragma once
#include <vector>
#include "ir.hpp"
#include "vm.hpp"

void run_program(struct MrLangVM* vm, std::vector<instruction> ir);
