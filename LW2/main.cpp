#include <iostream>
#include <algorithm>
#include <limits>

#include "include/hex.h"
#include "include/exceptions.h"

int main() {
    Hex *number = nullptr;
    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\nhex> ";
        std::string input;
        std::cin >> input;

        if (input == "exit")
            return 0;

        else if (input == "hex") {
            std::cout << "Введите шестнадцатеричное число: ";
            std::string inp;
            std::cin >> inp;
            
            try {
                number = new Hex(inp);
            } catch (NoHexNumericException) {
                std::cout << "Некорректный ввод!" << std::endl;
            }
        }

        else if (input == "decimal") {
            std::cout << "Введите десятичное число: ";
            unsigned long long int inp;
            std::cin >> inp;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
            } else number = new Hex(inp);
        }

        else if (input == "print") {
            if (number != nullptr)
                std::cout << *number << std::endl;
            else
                std::cout << "Число в настоящий момент не определено!" << std::endl;
        }

        else if (input == "help") {
            std::cout << "hex : ввести число в шестнадцатеричной форме" << std::endl;
            std::cout << "decimal : ввести число в десятичной форме" << std::endl;
            std::cout << "print : вывести число в шестнадцатеричной форме" << std::endl;
            std::cout << "exit : выход" << std::endl;
        }

        else std::cout << "Команда не найдена!" << std::endl;
    }
}