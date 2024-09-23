#include <iostream>
#include <algorithm>
#include "include/solver.h"

int main() {
    std::locale::global(std::locale("ru_RU.UTF-8"));
    
    std::string day;
    int number;

    std::cout << "Введите день недели:" << std::endl;
    std::cin >> day;

    std::cout << "Введите число:" << std::endl;
    std::cin >> number;
    
    auto result = solver(day, number);

    std::cout << result << std::endl;

    return 0;
}