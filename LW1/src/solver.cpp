#include <string> 
#include "../include/solver.h" 
 
bool solver(const std::string &day, int number) { 
    if ( 
            day == "Понедельник" && number == 12 || 
            day == "Вторник" && number > 95 || 
            day == "Среда" && number == 34 || 
            day == "Четверг" && number == 0 || 
            day == "Пятница" && number % 2 == 0 || 
            day == "Суббота" && number == 56 || 
            day == "Воскресенье" && abs(number / 666) == 1 
        ) 
        return true; 
    return false; 
}