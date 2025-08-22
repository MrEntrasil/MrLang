#include "interpreter.hpp"
#include "builtin.hpp"
#include <iostream>
#include <cstdlib>

void run_program(struct MrLangVM* vm, std::vector<instruction> ir) {
    for (size_t i = 0; i < ir.size(); i++) {
        instruction instr = ir[i];

        switch (instr.op) {
            case opcode::IDENT: {
                auto f = vm->funcs.find(instr.operand);
                if (f != vm->funcs.end()) f->second(vm);
                break;
            }
            case opcode::PUSH_STR:
                vm->st.push_back(instr.operand);
                break;
            case opcode::PUSH_NUM:
                vm->st.push_back(static_cast<int32_t>(std::stoi(instr.operand)));
                break;
            case opcode::POP:
                if (!vm->st.empty()) {
                    vm->st.pop_back();
                } else {
                    std::cerr << "interpreter error: stack is empty\n";
                    std::exit(1);
                }
                break;
            case opcode::CLEARSTACK:
                vm->st.clear();
                break;
            case opcode::END:
                return;
            case opcode::STORE:
                if (!vm->st.empty()) {
                    vm->vars[instr.operand] = vm->st.back();
                    vm->st.pop_back();
                } else {
                    std::cerr << "interpreter error: stack is empty!\n";
                    std::exit(1);
                }
                break;
            case opcode::LOAD: {
                auto val = vm->vars.find(instr.operand);
                if (val != vm->vars.end()) {
                    vm->st.push_back(val->second);
                    vm->vars.erase(val);
                } else {
                    std::cerr << "interpreter error: variable '" << instr.operand << "' not found!\n";
                    std::exit(1);
                }
                break;
            }
            default: break;
        }
    }
}

