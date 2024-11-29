#include <iostream>
#include <limits>

#include <editor.h>

int main() {
    auto rules = std::map({
        std::pair<std::string, std::string> {"werewolf", "robber"},
        std::pair<std::string, std::string> {"robber", "bear"},
        std::pair<std::string, std::string> {"bear", "werewolf"}
    });

    auto editor = Editor(rules);
    auto console_observer = std::make_shared<ConsoleObserver>(ConsoleObserver());
    auto file_observer = std::make_shared<FileObserver>(FileObserver("log.txt"));
    editor.add_observer(console_observer);
    editor.add_observer(file_observer);

    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\neditor> ";
        std::string input;
        std::cin >> input;

        if (input == "exit")
            return 0;

        if (input == "add") {
            std::string type, name;
            double x, y;
            std::cin >> type >> name >> x >> y;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
                continue;
            }

            try {
                editor.add_npc(type, name, x, y);
            } catch (UnknownNPCTypeException&) {
                std::cout << "Некорректный тип NPC ('werewolf', 'bear' или 'robber')!" << std::endl;
            }
        }

        else if (input == "load") {
            std::string filename;
            std::cin >> filename;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
                continue;
            }

            try {
                editor.load(filename);
            } catch (FileNotExistsException&) {
                std::cout << "Файл не найден!" << std::endl;
            } catch (UnknownNPCTypeException&) {
                std::cout << "Некорректный тип NPC ('werewolf', 'bear' или 'robber')!" << std::endl;
            } catch (InvalidCoordinatesExceptions&) {
                std::cout << "Некорректно заданы координаты!" << std::endl;
            }
        }

        else if (input == "save") {
            std::string filename;
            std::cin >> filename;

            if (!editor.empty()) {
                try {
                    editor.save(filename);
                } catch (FileNotExistsException&) {
                    std::cout << "Ошибка сохранения" << std::endl;
                }
            } else {
                std::cout << "Список NPC пуст!" << std::endl;
            }
        }

        else if (input == "print") {
            if (!editor.empty()) {
                editor.print();
            } else {
                std::cout << "Список NPC пуст!" << std::endl;
            }
        }

        else if (input == "fight") {
            double max_distance;
            std::cin >> max_distance;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
                continue;
            }

            if (!editor.empty()) {
                editor.fight(max_distance);
            } else {
                std::cout << "Список NPC пуст!" << std::endl;
            }
        }
        else if (input == "help") {
            std::cout << "add <type> <name> <x> <y> : добавить NPC типа type с именем name на точку (x, y)" <<
                std::endl;
            std::cout << "load <filename> : загрузить всех NPC из файла с именем filename" << std::endl;
            std::cout << "save <filename> : сохранить всех NPC в файл с именем filename" << std::endl;
            std::cout << "print : распечатать список NPC" << std::endl;
            std::cout << "fight <distance> : начать сражение на максимальной дистанции distance" << std::endl;
            std::cout << "exit : выход" << std::endl;
        }

        else std::cout << "Команда не найдена!" << std::endl;
    }
}
