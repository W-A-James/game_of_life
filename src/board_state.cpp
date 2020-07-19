#include "board_state.hpp"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

namespace Board {

State::State(std::uint32_t u32_num_rows, uint32_t u32_num_cols):
    u32_num_rows_(u32_num_rows), u32_num_cols_(u32_num_cols) {
    board_state_ = (std::uint8_t**) std::malloc(u32_num_rows * sizeof(std::uint8_t*));
    if (board_state_ == NULL) exit(1);       
    for (int i = 0; i < u32_num_rows; i++) {
        board_state_[i] = (std::uint8_t *)std::malloc(u32_num_cols * sizeof(std::uint8_t));
        if (board_state_[i] == NULL) exit(1);
        for (int j = 0; j < u32_num_cols; j++) {
            board_state_[i][j] = 0;
        }
    } 
}

State::~State() {
    for (int i = 0; i < u32_num_rows_; i++) {
        std::free(board_state_[i]);
    }
    std::free(board_state_);
}

const std::uint8_t State::get_val(const std::uint32_t u32_cell_num) const {
    if (u32_cell_num >= u32_num_rows_ * u32_num_cols_)
        throw std::out_of_range("Cell out of range");
    return (board_state_[u32_cell_num/u32_num_cols_][u32_cell_num%u32_num_cols_]);
}

const std::uint8_t State::get_val(const std::uint32_t u32_row, const uint32_t u32_col) const {
    if (u32_row >= u32_num_rows_ || u32_col >= u32_num_cols_)
        throw std::out_of_range("Cell out of range"); 
    return (board_state_[u32_row][u32_col]);
}

void State::set_val(const std::uint32_t u32_cell_num, const std::uint8_t val) {
    if (u32_cell_num >= u32_num_rows_ * u32_num_cols_)
        throw std::out_of_range("Cell out of range");
    if (val > 1) throw std::invalid_argument("val must be 0 or 1");
    board_state_[u32_cell_num/u32_num_cols_][u32_cell_num%u32_num_cols_] = val;
}

// Set val at board_state_[u32_row][u32_col]
// to val
// Return 0 if successful, return 1 otherwise
void State::set_val(const std::uint32_t u32_row,
             const std::uint32_t u32_col,
             const std::uint8_t val) {
    if (u32_row >= u32_num_rows_ || u32_col >= u32_num_cols_)
        throw std::out_of_range("Cell out of range"); 
    if (val > 1) throw std::invalid_argument("val must be 0 or 1");
    board_state_[u32_row][u32_col] = val;
}

void State::print(std::ostream& os) const {
    for (std::uint32_t i = 0; i < u32_num_rows_; i++) {
        for (std::uint32_t j = 0; j < u32_num_cols_; j++) {
            os << (int)board_state_[i][j] << " ";
        }
        os << "\n";
    }
}

}
