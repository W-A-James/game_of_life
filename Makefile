OBJFILES = src/change.o src/board_state.o src/life.o
CXXFLAGS = -std=c++14 -O2
CXX = emcc

all: target/life.js

target/life.js: $(OBJFILES) 
	emcc --bind $(CXXFLAGS) -o target/life.js $(OBJFILES)

src/%.o: src/%.cpp src/%.hpp
	emcc $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJFILES) target/life.js target/life.wasm test_*

