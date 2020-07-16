#pragma once

#include <queue>
#include <cinttypes>
#include "board_state.hpp"
#include "change.hpp"

extern std::queue<const Change::Change*>* changeQueue;
extern Board::State* board_state;
void step(const std::uint32_t, const std::uint32_t);
void reset_sim(const std::uint32_t, const std::uint32_t, const std::uint32_t);
void update_cell(const std::uint32_t, const std::uint32_t, const std::uint32_t);
void init_board(const std::uint32_t, const std::uint32_t);
void clear_cell(const std::uint32_t);
void fill_cell(const std::uint32_t);
void free_board();

