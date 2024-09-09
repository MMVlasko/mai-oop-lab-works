#include <iostream>
#include "include/solver.h"

int main() {
    setlocale(LC_ALL, "ru-RU");
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