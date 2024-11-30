#include <iostream>
#include <limits>

#include <editor.h>

int main() {
    auto rules = std::map({
        std::pair<std::string, std::string> {"werewolf", "robber"},
        std::pair<std::string, std::string> {"robber", "bear"},
        std::pair<std::string, std::string> {"bear", "werewolf"}
    });

    auto properties = std::map({
        std::pair<std::string, std::pair<int, int>> {"werewolf", {400, 50}},
        std::pair<std::string, std::pair<int, int>> {"robber", {100, 100}},
        std::pair<std::string, std::pair<int, int>> {"bear", {50, 100}}
    });

    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\neditor> ";
        std::string input;
        std::cin >> input;

        if (input == "exit")
            return 0;

        if (input == "go") {
            int ms, size;
            std::cin >> ms >> size;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
                continue;
            }

            try {
                auto editor = Editor(rules, properties, size);
                auto file_observer = std::make_shared<FileObserver>(FileObserver("log.txt"));
                editor.add_observer(file_observer);
                editor.process(ms);
            } catch (...) {
                std::cout << "Неизвестная ошибка!" << std::endl;
            }
        }
        else if (input == "help") {
            std::cout << "go <ms> <size>: начать 30-секундный сеанс на поле размером size x size с задержкой между "
                         "циклами ms миллисекунд" << std::endl;
            std::cout << "exit : выход" << std::endl;
        }

        else std::cout << "Команда не найдена!" << std::endl;
    }
}
