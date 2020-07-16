#pragma once
#include <cstdio>

void success(const char* program_name) {
    std::printf("%s ran without any errors!\n", program_name);
}
