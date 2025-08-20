CXX=ccache clang++
CXXFLAGS=-O0 -g -include mrlang.hpp -std=c++17
TARGET=mrlang
FILES=./main.cpp

all:
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)

pch:
	clang++ -std=c++17 -O0 -g -x c++-header ./mrlang.hpp -o mrlang.hpp.gch
