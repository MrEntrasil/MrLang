cmake_minimum_required(VERSION 3.12)
project(MrLang LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SOURCES
	main.cpp
	core/lexer.cpp
	core/ir.cpp
	core/interpreter.cpp
	core/builtin.cpp
	core/error.cpp
	core/vm.cpp
)

add_executable(mrlang ${SOURCES})
