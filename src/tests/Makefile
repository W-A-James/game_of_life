NATIVE_OBJ_FILES = change.nobj board_state.nobj life.nobj
TEST_FILES = change.t board_state.t life.m.t profiling

all: $(TEST_FILES) 

life.m.t : life.t.cpp $(NATIVE_OBJ_FILES)
	g++ -std=c++14 -o life.m.t life.t.cpp $(NATIVE_OBJ_FILES)

%.nobj: ../%.cpp
	g++ -std=c++14 -c $< -o $@ -D NO_EMSCRIPTEN

%.t: %.t.cpp %.nobj
	g++ -std=c++14 -o $@ $^

profiling: profiling.t.cpp $(NATIVE_OBJ_FILES)
	g++ -std=c++14 -o $@ $^
    
.PHONY: clean

clean:
	rm -f $(NATIVE_OBJ_FILES) *.t

tests: $(TEST_FILES)
