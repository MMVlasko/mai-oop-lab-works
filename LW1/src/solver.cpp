#include <string> 
#include "../include/solver.h" 
 
bool solver(const std::string& day, int number) { 
    return day == "понедельник" && number == 12 || 
            day == "вторник" && number > 95 || 
            day == "среда" && number == 34 || 
            day == "четверг" && number == 0 || 
            day == "пятница" && number % 2 == 0 || 
            day == "суббота" && number == 56 || 
            day == "воскресенье" && abs(number / 666) == 1;
}