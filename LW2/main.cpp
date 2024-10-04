#include <iostream>
#include <algorithm>
#include <limits>

#include <hex.h>
#include <exceptions.h>

int main() {
    Hex *first_number = nullptr;
    Hex *second_number = nullptr;
    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\nhex> ";
        std::string input;
        std::cin >> input;

        if (input == "exit") {
            delete first_number;
            delete second_number;
            return 0;
        }

        else if (input == "hex1" || input == "hex2") {
            std::cout << "Введите шестнадцатеричное число: ";
            std::string inp;
            std::cin >> inp;
            
            try {
                if (input == "hex1")
                    first_number = new Hex(inp);
                else second_number = new Hex(inp);
            } catch (NoHexNumericException) {
                std::cout << "Некорректный ввод!" << std::endl;
            }
        }

        else if (input == "dec1" || input == "dec2") {
            std::cout << "Введите десятичное число: ";
            unsigned long long int inp;
            std::cin >> inp;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
            } else {
                if (input == "dec1")
                    first_number = new Hex(inp);
                else second_number = new Hex(inp);
            }
        }

        else if (input == "print") {
            if (first_number != nullptr) {
                std::cout << *first_number << std::endl;
            }
            else
                std::cout << "Первое число в настоящий момент не определено!" << std::endl;

            if (second_number != nullptr) {
                std::cout << *second_number << std::endl;
            }
            else
                std::cout << "Второе число в настоящий момент не определено!" << std::endl;
        }

        else if (input == "+" || input == "-" || input == ">" || input == "<" || input == ">=" || 
                input == "<=" || input == "==" || input == "!=") {
            try {
                if (first_number == nullptr)
                    std::cout << "Первое число не определено!" << std::endl;
                else if (second_number == nullptr)
                    std::cout << "Второе число не определено!" << std::endl;
                else {
                    if (input == "+") {
                        auto result = *first_number + *second_number;
                        std::cout << result << std::endl;
                    } else if (input == "-") {
                        try {
                            auto result = *first_number - *second_number;
                            std::cout << result << std::endl;
                        } catch (ResultIsNegativeException) {
                            std::cout << "Отрицательный результат!" << std::endl;
                        }
                    } else if (input == ">") {
                        auto result = *first_number > *second_number;
                        std::cout << result << std::endl;
                    } else if (input == "<") {
                        auto result = *first_number < *second_number;
                        std::cout << result << std::endl;
                    } else if (input == ">=") {
                        auto result = *first_number >= *second_number;
                        std::cout << result << std::endl;
                    } else if (input == "<=") {
                        auto result = *first_number - *second_number;
                        std::cout << result << std::endl;
                    } else if (input == "==") {
                        auto result = *first_number == *second_number;
                        std::cout << result << std::endl;
                    } else if (input == "!=") {
                        auto result = *first_number != *second_number;
                        std::cout << result << std::endl;
                    }
                }
            } catch (TooBigNumberException) {
                std::cout << "Слишком большие числа для выполнения операций!" << std::endl;
            }
        }

        else if (input == "help") {
            std::cout << "hex1/hex2 : ввести первое/второе число в шестнадцатеричной форме" << std::endl;
            std::cout << "dec1/dec2 : ввести первое/второе число в десятичной форме" << std::endl;
            std::cout << "print : вывести числа в шестнадцатеричной форме" << std::endl;
            std::cout << "+/- : вывести результат сложения/вычитания чисел в шестнадцатеричной форме" << std::endl;
            std::cout << ">/</>=/<=/==/!= : вывести результат сравнения чисел" << std::endl;
            std::cout << "exit : выход" << std::endl;
        }

        else std::cout << "Команда не найдена!" << std::endl;
    }
}