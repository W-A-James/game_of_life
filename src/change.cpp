#include "change.hpp"
namespace Change {
Type Change::getType() const {
    return type_;
}

std::uint32_t Change::getCell() const {
    return cell_num_;
}

}
