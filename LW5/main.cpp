#include <iostream>
#include <limits>

#include <stack_memory_resource.h>
#include <stack.h>

struct Pair {
    int x;
    int y;
};

int main() {
    StackMemoryResource mr1;
    auto int_stack = Stack<int>(&mr1);

    StackMemoryResource mr2;
    auto pair_stack = Stack<Pair>(&mr2);

    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\nstack> ";
        std::string input;
        std::cin >> input;

        if (input == "exit")
            return 0;

        if (input == "push") {
            std::string type;
            std::cin >> type;

            if (type == "int") {
                int elem;
                std::cin >> elem;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод!" << std::endl;
                    continue;
                }

                try {
                    int_stack.push(elem);
                } catch (OutOfMemoryException&) {
                    std::cout << "Стек переполнен!" << std::endl;
                }
            }

            else if (type == "pair") {
                Pair pair{};
                std::cin >> pair.x >> pair.y;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Некорректный ввод!" << std::endl;
                    continue;
                }
                try {
                    pair_stack.push(pair);
                } catch (OutOfMemoryException&) {
                    std::cout << "Стек переполнен!" << std::endl;
                }
            }

            else
                std::cout << "Некорректный параметр 'type'!" << std::endl;
        }

        else if (input == "print") {
            std::string type;
            std::cin >> type;

            if (type == "int")
                std::cout << int_stack << std::endl;

            else if (type == "pair") {
                std::cout << ']';
                for (auto [x, y]: pair_stack)
                    std::cout << " (" << x << ", " << y << ')';
                std::cout << ']' << std::endl;
            }

            else
                std::cout << "Некорректный параметр 'type'!" << std::endl;
        }

        else if (input == "pop") {
            std::string type;
            std::cin >> type;

            if (type == "int")
                try {
                    std::cout << *int_stack.pop() << std::endl;
                } catch (EmptyStackException&) {
                    std::cout << "Стек пуст!" << std::endl;
                }

            else if (type == "pair")
                try {
                    const auto pair = pair_stack.pop();
                    std::cout << " (" << pair->x << ", " << pair->y << ')';
                } catch (EmptyStackException&) {
                    std::cout << "Стек пуст!" << std::endl;
                }

            else
                std::cout << "Некорректный параметр 'type'!" << std::endl;
        }

        else if (input == "clear") {
            std::string type;
            std::cin >> type;

            if (type == "int")
                int_stack.clear();

            else if (type == "pair")
                pair_stack.clear();

            else
                std::cout << "Некорректный параметр 'type'!" << std::endl;
        }

        else if (input == "size") {
            std::string type;
            std::cin >> type;

            if (type == "int")
                std::cout << int_stack.size() << std::endl;

            else if (type == "pair")
                std::cout << pair_stack.size() << std::endl;

            else
                std::cout << "Некорректный параметр 'type'!" << std::endl;
        }

        else if (input == "help") {
            std::cout << "push int/pair число/пара чисел : добавить число/пару чисел" << std::endl;
            std::cout << "print int/pair : вывести стек чисел/пар чисел" << std::endl;
            std::cout << "pop int/pair : удалить и вывести верхнее число/пару чисел стека" << std::endl;
            std::cout << "clear int/pair : очистить стек чисел/пар чисел" << std::endl;
            std::cout << "size int/pair : вывести размер стека чисел/пар чисел" << std::endl;
            std::cout << "exit : выход" << std::endl;
        }

        else std::cout << "Команда не найдена!" << std::endl;
    }
}