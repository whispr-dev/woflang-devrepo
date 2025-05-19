# plugins/Makefile

CXX := g++
CXXFLAGS := -std=c++17 -fPIC -Wall -Wextra -shared

SRC := $(wildcard *.cpp)
OUT := $(SRC:.cpp=.so)

all: $(OUT)

%.so: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.so
