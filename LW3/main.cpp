#include <limits>
#include <iostream>

#include <array.h>
#include <rectangle.h>
#include <square.h>
#include <trapeze.h>

int main() {
    auto *figures = new Array<Figure>();
    std::cout << "Type 'help' to get info" << std::endl;

    while (true) {
        std::cout << "\nfigure> ";
        std::string input;
        std::cin >> input;

        if (input == "exit") {
            figures->free_elements();
            delete figures;
            return 0;
        }

        if (input == "input") {
            int param;
            std::cout << "Выберите тип фигуры (1 - прямоугольник, 2 - квадрат, 3 - трапеция): ";
            std::cin >> param;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
            }
            
            else if (param == 1) {
                auto *rectangle = new Rectangle();
                try {
                    std::cin >> *rectangle;
                    figures->add(rectangle);
                } catch (BadInputDataException&) {
                    std::cout << "Введённая фигура не является прямоугольником!" << std::endl;
                    delete rectangle;
                }
            }

            else if (param == 2) {
                auto *square = new Square();
                try {
                    std::cin >> *square;
                    figures->add(square);
                } catch (BadInputDataException&) {
                    std::cout << "Введённая фигура не является квадратом!" << std::endl;
                    delete square;
                }
            }

            else if (param == 3) {
                auto *trapeze = new Trapeze();
                try {
                    std::cin >> *trapeze;
                    figures->add(trapeze);
                } catch (BadInputDataException&) {
                    std::cout << "Введённая фигура не является трапецией!" << std::endl;
                    delete trapeze;
                }
            }

            else std::cout << "Некорректный ввод!" << std::endl;
        }

        else if (input == "info") {
            if (!figures->size)
                std::cout << "Список фигур пуст!" << std::endl;
            else {
                for (int i = 0; i < figures->size; ++i) {
                    Point *center = (*figures)[i]->get_center();
                    std::cout << *(*figures)[i] << " Площадь: " << static_cast<double>(*(*figures)[i]) <<
                        " Центр: " << *center << std::endl;
                    delete center;
                }
            }
        }

        else if (input == "square") {
            if (!figures->size)
                std::cout << 0 << std::endl;
            else {
                double square = 0.;
                for (int i = 0; i < figures->size; ++i)
                    square += static_cast<double>(*(*figures)[i]);
                std::cout << square << std::endl;
            }
        }

        else if (input == "pop") {
            int index;
            std::cout << "Введите индекс удаляемой фигуры: ";
            std::cin >> index;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Некорректный ввод!" << std::endl;
            } else {
                try {
                    const Figure *poped = figures->pop(index);
                    std::cout << *poped << " удалена" << std::endl;
                    delete poped;
                } catch (IndexOutOfRangeException&) {
                    std::cout << "Элемент с указанным индексом не существвует!" << std::endl;
                }
            }
        }

        else if (input == "help") {
            std::cout << "input : ввести фигуру" << std::endl;
            std::cout << "info : вывести информацию о всех фигурах" << std::endl;
            std::cout << "square : вывести суммарну площадь фигур" << std::endl;
            std::cout << "pop : удалить фигуру по индексу" << std::endl;;
            std::cout << "exit : выход" << std::endl;
        }

        else std::cout << "Команда не найдена!" << std::endl;
    }
}