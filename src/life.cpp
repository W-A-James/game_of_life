#ifndef NO_EMSCRIPTEN
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#else
#include "life.hpp"
#endif

#include <queue>
#include <cstdlib>
#include <cinttypes>

#include "change.hpp"
#include "board_state.hpp"

#define TRUE_ 1
#define FALSE_ 0

std::queue<const Change::Change*>* changeQueue;
std::queue<std::uint32_t> * recentChangeQueue;
Board::State* board_state = NULL;
#ifndef NO_EMSCRIPTEN
using namespace emscripten;

val numRows = val::global("numRows");
val numCols = val::global("numCols");

// Bring in functions that modify the display in browser
EM_JS(void, update_cell_display, (std::uint32_t cell_num, bool change), {
        board_deltas.push({cellNum: cell_num, changeTo: change});
        }
    );
#endif



// Set board_state entry which corresponds to cell_num
// to 0 
void clear_cell(const std::uint32_t u32_cell_num) {
    board_state->set_val(u32_cell_num, FALSE_);
}

// Set board_state entry which corresponds to cell_num
// to 1 
void fill_cell(const std::uint32_t u32_cell_num) {
    board_state->set_val(u32_cell_num, TRUE_);
}

#ifndef NO_EMSCRIPTEN
void fill_cell_(const val cell_num) {
    fill_cell(cell_num.as<std::uint32_t>());
}

void clear_cell_(const val cell_num) {
    clear_cell(cell_num.as<std::uint32_t>());
}
#endif

// Add appropriate change to changeQueue for the cell provided as cell_num
// this implements edge-wrapping
void update_cell(const std::uint32_t u32_cell_num,
                const std::uint32_t u32_num_rows,
                const std::uint32_t u32_num_cols) {
    const std::uint32_t u32_col = u32_cell_num % u32_num_cols;
    const std::uint32_t u32_row = u32_cell_num / u32_num_cols; 
    std::uint32_t u32_num_neighbours = 0;
    std::uint32_t u32_above_row;
    std::uint32_t u32_below_row;
    std::uint32_t u32_left_col;
    std::uint32_t u32_right_col;

    // check above
    if (u32_row == 0) u32_above_row = u32_num_rows - 1;
    else u32_above_row = u32_row - 1;
    if (board_state->get_val(u32_above_row, u32_col) == TRUE_) u32_num_neighbours++;   

    // check top-left
    if (u32_col == 0) u32_left_col = u32_num_cols - 1;
    else u32_left_col = u32_col - 1;
    if (board_state->get_val(u32_above_row, u32_left_col) == TRUE_) u32_num_neighbours++;

    // check top-right
    if (u32_col == u32_num_cols - 1) u32_right_col = 0;
    else u32_right_col = u32_col + 1;
    if (board_state->get_val(u32_above_row, u32_right_col) == TRUE_) u32_num_neighbours++;

    // check below
    if (u32_row == u32_num_rows - 1) u32_below_row = 0;
    else u32_below_row = u32_row + 1;
    if (board_state->get_val(u32_below_row, u32_col) == TRUE_) u32_num_neighbours++;

    // check bottom left
    if (board_state->get_val(u32_below_row, u32_left_col)  == TRUE_) u32_num_neighbours++;
    // check bottom right
    if (board_state->get_val(u32_below_row, u32_right_col) == TRUE_) u32_num_neighbours++;

    // check left
    if (board_state->get_val(u32_row, u32_left_col) == TRUE_) u32_num_neighbours++;
    // check right
    if (board_state->get_val(u32_row, u32_right_col) == TRUE_) u32_num_neighbours++;

    if (board_state->get_val(u32_row, u32_col) == TRUE_) {
        switch (u32_num_neighbours) {
            case 2:
            case 3:
                break;
            default:
                changeQueue->push(new Change::Change(u32_cell_num, Change::DEAD));
#               ifndef NO_EMSCRIPTEN
                update_cell_display(u32_cell_num, false);
#               endif
                break;
        }
    }
    else {
        switch (u32_num_neighbours) {
            case 3:
                changeQueue->push(new Change::Change(u32_cell_num, Change::ALIVE));
#               ifndef NO_EMSCRIPTEN
                update_cell_display(u32_cell_num, true);
#               endif
                break;
            default:
                break;
        } 
    }
}

void reset_sim(const std::uint32_t u32_num_rows, const std::uint32_t u32_num_cols) {
    for (std::uint32_t i = 0; i < u32_num_rows; i++) {
        for (std::uint32_t j = 0; j < u32_num_cols; j++) {
            if (board_state->get_val(i, j)) {
                board_state->set_val(i, j, FALSE_);            
                changeQueue->push(new Change::Change(i*u32_num_cols + j, Change::DEAD));
#               ifndef NO_EMSCRIPTEN
                update_cell_display(i * u32_num_cols + j, false);
#               endif
            }
        }
    }
}


// Advance the simulation by one step
void step(const std::uint32_t u32_num_rows, const std::uint32_t u32_num_cols) {
    // TODO: use the contents of recentChangeQueue instead of brute-forcing
    for (std::uint32_t i = 0; i < u32_num_rows; i++) {
        for (std::uint32_t j = 0; j < u32_num_cols; j++) {
            update_cell(i * u32_num_cols + j, u32_num_rows, u32_num_cols);
        }
    }    

    while (!changeQueue->empty()) {
        const Change::Change* change = changeQueue->front();
        switch (change->getType()) {
            case Change::DEAD:
                clear_cell(change->getCell());
                break;
            case Change::ALIVE:
                fill_cell(change->getCell());
                break;
        }        
        //recentChangeQueue->push(change->getCell());
        delete change;
        changeQueue->pop();
    }
}

void init_board(const std::uint32_t u32_num_rows, const std::uint32_t u32_num_cols) {
    board_state = new Board::State(u32_num_rows, u32_num_cols);
    changeQueue = new std::queue<const Change::Change*>();
    // recentChangeQueue = new std::queue<std::uint32_t>();
}

void free_board() {
    delete board_state;
    delete changeQueue;
    //delete recentChangeQueue;
}

#ifndef NO_EMSCRIPTEN

void live_init() {
    init_board(numRows.as<std::uint32_t>(), numCols.as<std::uint32_t>());
}

void step_() {
    step(numRows.as<std::uint32_t>(), numCols.as<std::uint32_t>());
}

void reset_sim_() {
    reset_sim(numRows.as<std::uint32_t>(), numCols.as<std::uint32_t>());
}


EMSCRIPTEN_BINDINGS(my_module) {
    function("step", &step_);
    function("reset_sim", &reset_sim_);
    function("clear_cell_", &clear_cell_);
    function("fill_cell_", &fill_cell_);
    function("update_cell", &update_cell);
    function("init_board", &live_init);
    function("free_board", &free_board);
}
#endif

