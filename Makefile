CXX=clang++
CXXFLAGS=-std=c++17
TARGET=mrlang
FILES=./main.cpp

all:
	$(CXX) $(CXXFLAGS) $(FILES) -o $(TARGET)
