#include <iostream>

#include <tools.h>
#include <exceptions.h>

void check_cin() {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw BadInputDataException("Incorrect input");
    }
}