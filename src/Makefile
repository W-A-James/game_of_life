OBJFILES = change.o board_state.o life.o
CXXFLAGS = -std=c++14 -O2
CXX = emcc

all: ../target/life.js

../target/life.js: $(OBJFILES) 
	emcc --bind $(CXXFLAGS) -o ../target/life.js $(OBJFILES)

%.o: %.cpp %.hpp
	emcc $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJFILES) ../static/target/life.js ../static/target/life.wasm test_*

