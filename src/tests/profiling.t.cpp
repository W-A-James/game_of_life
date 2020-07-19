#include <chrono>
#include <iostream>
#include <cstdio>
#include <cinttypes>
#include <random>
#include <vector>
#include <string>

#include "../life.hpp"

// profile step
void profile_step(const std::uint32_t n, const std::uint32_t num_steps, const double frac_full) {
    init_board(n, n); 
    std::uint32_t num_full = 0;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, (n*n) - 1);
    while (num_full/(n*n) < frac_full) {
        std::uint32_t cell_num = distrib(gen);
        fill_cell(cell_num);
        num_full++;
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (std::uint32_t i = 0; i < num_steps; i++) {
        step(n, n);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::printf("| n = %4d | num_steps = %4d | frac_full: %.2f | time_elapsed: %4.3fs |\n", n, num_steps, frac_full, elapsed.count());
    free_board(); 
}

int main(int argc, char** argv) {
    // arg 1 is num of steps to take
    // args 2... are the size of one size of the board grid
    if (argc < 3) {
        std::cout << "should be of form 'profiling <num_steps> <size0> <size1> ... <sizeN>'\n";
        return 1;
    }
    std::uint32_t num_steps = std::stoi(argv[1]);
    for (int i = 2; i < argc; i++) { 
        profile_step(std::stoi(argv[i]), num_steps, 0.2); 
    }
    return 0;
}
