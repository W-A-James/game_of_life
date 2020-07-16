#pragma once
#include <cinttypes>

namespace Change {

enum Type {ALIVE, DEAD};

class Change {
    private:
        std::uint32_t cell_num_;
        Type type_;
    public:
        std::uint32_t getCell() const;
        Type getType() const;
        Change(std::uint32_t cell_num, Type type): cell_num_(cell_num), type_(type) {}
};

} // namespace Change
