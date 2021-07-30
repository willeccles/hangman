SRC = $(wildcard *.cpp)
OBJ = $(patsubst %,build/%.o,$(SRC))
DEP = $(wildcard build/*.d)

CXXFLAGS += -std=c++20 -O3 -W -Wall -pedantic

-include $(DEP)

.PHONY: all format clean

all: hangman

hangman: $(OBJ) | build
	$(CXX) $(LDFLAGS) -o "$@" $^

build/%.o: % | build
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o "$@" "$<"

build:
	mkdir -p $@

format:
	clang-format --verbose -i *.cpp *.h

clean:
	rm -rf build
