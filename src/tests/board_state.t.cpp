#include "../board_state.hpp"
#include <cassert>
#include <iostream>
#include <cstdlib>
#include <type_traits>
#include <stdexcept>

#define assertm(exp, msg) assert(((void)msg, exp))

void test_constructor() {
    Board::State* p_bs = new Board::State(1,1);
    assert(p_bs != NULL);
    std::cout << "Constructor tests passed!\n";
}

// check getters
void test_get_set() {
    std::uint32_t num_rows = 10;
    std::uint32_t num_cols = 10;
    bool caught_overflow0 = false;
    bool caught_overflow1 = false;
    bool caught_overflow2 = false;
    bool caught_overflow3 = false;
    Board::State* p_bs = new Board::State(num_rows, num_cols);
    assert(p_bs != NULL);
    for (std::uint32_t i = 0; i < p_bs->get_num_rows(); i++) {
        for (std::uint32_t j = 0; j < p_bs->get_num_cols(); j++) {
            assert(p_bs->get_val(i, j) == 0);
            p_bs->set_val(i, j, 1);
            assert(p_bs->get_val(i, j) == 1);
        }
    }

    // test with values out of range
    try {
       p_bs->get_val(num_rows * num_cols); 
    }
    catch (const std::out_of_range&) {
       caught_overflow0 = true; 
    }

    try {
       p_bs->get_val(num_rows, num_cols); 
    }
    catch (const std::out_of_range&) {
        caught_overflow1 = true;
    }


    try {
       p_bs->set_val(num_rows * num_cols, 0); 
    }
    catch (const std::out_of_range&) {
        caught_overflow2 = true;    
    }

    try {
       p_bs->set_val(num_rows, num_cols, 0); 
    }
    catch (const std::out_of_range&) {
       caught_overflow3 = true; 
    }
    assertm(caught_overflow0, "Failed to catch overflow with State::get_val(uint32_t cell_num)\n");
    assertm(caught_overflow1, "Failed to catch overflow with State::get_val(uint32_t row_num, uin32_t col_num)\n");
    assertm(caught_overflow2, "Failed to catch overflow with State::set_val(uint32_t cell_num, uint8_t val)\n");
    assertm(caught_overflow3, "Failed to catch overflow with State::set_val(uint32_t row_num, uin32_t col_num, uint8_t val)\n");
    std::cout << "Getter tests passed!\n"; 
}

void test_get_ptr_at() {
    std::uint32_t num_rows =10;
    std::uint32_t num_cols = 10;
    bool caught_overflow0 = false;
    bool caught_overflow1 = false;
    Board::State* p_bs = new Board::State(num_rows, num_cols);
    assert(p_bs != NULL);

    auto p_u8 = p_bs->get_ptr_at(0, 0);
    // attempt to modify content of pointer (should be allowed)
    *p_u8 = 1;
    assert(p_bs->get_val(0, 0) == 1);

    try {
       p_bs->get_ptr_at(num_rows * num_cols); 
    }
    catch (const std::out_of_range&) {
       caught_overflow0 = true; 
    }

    try {
       p_bs->get_ptr_at(num_rows, num_cols); 
    }
    catch (const std::out_of_range&) {
        caught_overflow1 = true;
    }


    
    assertm(caught_overflow0, "Failed to catch overflow with State::get_val(uint32_t cell_num)\n");
    assertm(caught_overflow1, "Failed to catch overflow with State::get_val(uint32_t row_num, uin32_t col_num)\n");

    std::cout << "ptr tests passed!\n";

    // test with out of range
}

int main() {
    test_constructor();
    test_get_set();
    test_get_ptr_at();
    return 0;
}
