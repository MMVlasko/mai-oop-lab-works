#include "../include/tools.h"


unsigned char get_hex_numeric(unsigned int numeric) {
    auto symbols = "012346789ABCDEF";
    return symbols[numeric];
}

unsigned int get_decimal_numeric(unsigned char numeric) {
    auto symbols = "012346789ABCDEF";
    for (int i = 0; i < 16; ++i)
        if (symbols[i] == numeric)
            return i;
}