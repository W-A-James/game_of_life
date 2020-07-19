#pragma once
#include <cinttypes>
#include <array>
#include <iostream>

namespace Board {

class State {
    public:

        State(std::uint32_t, uint32_t);

        ~State();

        // should throw invalid argument exception when out of range
        const std::uint8_t get_val(const std::uint32_t) const;
        const std::uint8_t get_val(const std::uint32_t, const uint32_t) const;

        // should throw invalid argument exception when out of range
        void set_val(const std::uint32_t, const std::uint8_t);
        void set_val(const std::uint32_t,
                     const std::uint32_t,
                     const std::uint8_t);

        const std::uint32_t get_num_rows() const { return u32_num_rows_; }
        const std::uint32_t get_num_cols() const { return u32_num_cols_; }

        void print(std::ostream& os) const;

        friend std::ostream& operator<<(std::ostream& os, const State& b) {
             b.print(os);
             return os;
         }

        // TODO: implement resizing
        void resize(std::uint32_t, std::uint32_t);
    private:
        // 2d array of 0s or 1s which contains board state
        // NOTE: cannot make this pointer const as we may need to resize it in future
        // TODO: Determine const declaration of this to ensure that the individual
        //       elements of the arrays which consist this can be modified, but the pointers
        //       themselves cannot be reassigned
        std::uint8_t ** board_state_;
 
        // dimensions of board
        // NOTE: these also cannot be made const as we may need to resize in future
        std::uint32_t u32_num_rows_, u32_num_cols_;
        
        // private helper function to convert from right-to-left counted cell number
        // to [<row_num>, <col_num>]
        const std::array<std::uint32_t, 2> cell_name_to_row_col_pair(std::uint32_t u32_cell_num)
        {
            std::array<std::uint32_t, 2> rv = {0, 0};    
            rv[0] = u32_cell_num / u32_num_cols_;
            rv[1] = u32_cell_num % u32_num_cols_;

            return rv;
        }
};

} // namespace
