#pragma once
#include <string>

void MrLangError_stacksize(size_t s, std::string funcname);
void MrLangError_wrongtype(std::string expected_type, std::string funcname);
