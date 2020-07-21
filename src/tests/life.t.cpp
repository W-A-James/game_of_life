#include "../life.hpp"
#include "../change.hpp"
#include "../board_state.hpp"
#include <cinttypes>
#include <cassert>
#include "test.hpp"
#include <iostream>

void test_init_board() {
    init_board(10, 10);
    assertm(board_state->get_num_rows() == 10, "init_board() failed! Incorrect number of rows\n");
    assertm(board_state->get_num_cols() == 10, "init_board() failed! Incorrect number of columns\n");
    std::cout << "test_init_board() passed!\n";
}

void test_free_board() {
    init_board(10, 10);
    std::array<std::uint8_t*, 10> pointers;
    free_board();
    std::cout << "test_free_board() passed!\n";
}

void test_fill_cell() {
    std::uint32_t u32_num_rows;
    std::uint32_t u32_num_cols;
    init_board(10, 10);
    u32_num_rows = board_state->get_num_rows();
    u32_num_cols = board_state->get_num_cols();
    fill_cell(0);
    assertm(board_state->get_val(0) == 1, "fill_cell() failed!\n");
    std::cout << "test_fill_cell() passed!\n";
}
void test_clear_cell() {
    std::uint32_t u32_num_rows;
    std::uint32_t u32_num_cols;
    init_board(10, 10);
    u32_num_rows = board_state->get_num_rows();
    u32_num_cols = board_state->get_num_cols();
    fill_cell(0);
    clear_cell(0);
    assertm(board_state->get_val(0) == 0, "clear_cell() failed!\n");
    std::cout << "test_clear_cell() passed!\n";
}

void test_update_cell() {
    init_board(3, 3);
    // live cell with < 2 live neighbours
    fill_cell(4);
    fill_cell(3);
    update_cell(4, board_state->get_num_rows(), board_state->get_num_cols());

    assertm(changeQueue->front()->getType() == Change::DEAD, "Update failed with live cell with <2 neighbours\n");
    assertm(changeQueue->front()->getCell() == 4, "update_cell() failed with live cell with <2 neighbours");

    changeQueue->pop();
    // live cell with 2, 3 live neighbours
    fill_cell(5);

    update_cell(4, board_state->get_num_rows(), board_state->get_num_cols());
    assertm(changeQueue->size() == 0, "update_cell() failed with cell with 2 neighbours\n");

    fill_cell(6);
    update_cell(4, board_state->get_num_rows(), board_state->get_num_cols());
    assertm(changeQueue->size() == 0, "update_cell() failed with cell with 3 neighbours\n");
    // live cell with more than 3 live neighbours
    fill_cell(8);
    update_cell(4, board_state->get_num_rows(), board_state->get_num_cols());
    assertm(changeQueue->front()->getType() == Change::DEAD, "update_cell() failed with cell with >3 neighbours\n");
    changeQueue->pop();
    // dead cell with 3 live neighbours
    clear_cell(4);
    clear_cell(8); 
    update_cell(4, board_state->get_num_rows(), board_state->get_num_cols());

    assertm(changeQueue->front()->getType() == Change::ALIVE, "update_cell() failed with cell with 3 neighbours\n");
    changeQueue->pop();

    fill_cell(7);
    fill_cell(8);
    update_cell(7, board_state->get_num_rows(), board_state->get_num_cols());
    assertm(changeQueue->front()->getType() == Change::DEAD, "update_cell() failed with live cell with 4 neighbours\n");
    // test edges and wrap-around
    std::cout << "test_update_cell() passed!\n";
}

void test_reset_sim() {

}

void test_step() {
    init_board(5, 5);
    fill_cell(7);
    fill_cell(11);
    fill_cell(18);

    std::cout << *board_state << "\n";
    step(board_state->get_num_rows(), board_state->get_num_cols());
    std::cout << *board_state << "\n";
    assertm(board_state->get_val(12) == 1, "step() failed!\n");

    step(board_state->get_num_rows(), board_state->get_num_cols());
    std::cout << *board_state << "\n";

    for (std::uint32_t i = 0; i < 25; i++) {
        assertm(board_state->get_val(i) == 0, "step() failed!\n");
    }
    
    fill_cell(12);
    fill_cell(13);
    fill_cell(11);

    step(board_state->get_num_rows(), board_state->get_num_cols());
    std::cout << *board_state << "\n";
    assert(board_state->get_val(7) == 1);
    assert(board_state->get_val(12) == 1);
    assert(board_state->get_val(17) == 1);

    step(board_state->get_num_rows(), board_state->get_num_cols());
    std::cout << *board_state << "\n";
    assert(board_state->get_val(11) == 1);
    assert(board_state->get_val(12) == 1);
    assert(board_state->get_val(13) == 1);

    step(board_state->get_num_rows(), board_state->get_num_cols());
    std::cout << *board_state << "\n";
    assert(board_state->get_val(7) == 1);
    assert(board_state->get_val(12) == 1);
    assert(board_state->get_val(17) == 1);

    std::cout << "test_step() passed!\n";
}

int main() {
    test_init_board();
    test_fill_cell();
    test_clear_cell();
    test_update_cell();
    test_reset_sim();
    test_step();
    test_free_board();
    return 0;
}
