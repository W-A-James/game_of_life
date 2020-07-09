#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <queue>

class Change {
    private:
        unsigned int cell_num_;
    public:
        unsigned int getCell();
        Change(unsigned int cell_num): cell_num_(cell_num) {}
}

using namespace emscripten;

var numRows = var::global("numRows");
var numCols = var::global("numCols");
var boardState = var::global("boardState");
queue<Change&> changeQueue = new queue<Change&>();

// Set boardState entry which corresponds to cell_num
// to false
void clear_cell(unsigned int cell_num) {

}

// Set boardState entry which corresponds to cell_num
// to true
void fill_cell(unsigned int cell_num) {

}

// Add appropriate change to changeQueue for the cell provided as cell_num
void update_cell(unsigned int cell_num) {

}

// Advance the simulation by one step
void step() {
    //    TODO: cast numRows and numCols to unsigned int
    //    unsigned int num_rows_uint =  
    for (unsigned int i = 0; i < numRows; i++) {
        for (unsigned int j = 0; j < numCols; j++) {
            update_cell(i * numRows + j);
        }
    }    
}
