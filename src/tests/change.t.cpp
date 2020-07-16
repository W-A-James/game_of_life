#include "../change.hpp"
#include "test.h"
#include <cassert>
#include <cstdio>

void test_constructor_and_getters() {
    Change::Change c0 = Change::Change(0, Change::ALIVE);
    assert(c0.getCell() == 0);
    assert(c0.getType() == Change::ALIVE);

    Change::Change c1 = Change::Change(1, Change::DEAD);
    assert(c1.getCell() == 1);
    assert(c1.getType() == Change::DEAD);
}

void test_attempt_at_changing_fields() {

}

int main(int argc, const char** argv) {
    test_constructor_and_getters();
    success(argv[0]);
    return 0;
}
