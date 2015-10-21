CXX=clang++
CXXFLAGS=-std=c++11 -pedantic
BIN=intlex

SRC=$(wildcard *.cpp)

all: $(SRC)
	$(CXX) $(CXXFLAGS) -o $(BIN) $^

clean:
	rm $(BIN)
