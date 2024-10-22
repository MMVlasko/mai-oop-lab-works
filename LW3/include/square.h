#pragma once

#include "figure.h"

class Square : public Figure {
    public:
        using Figure::Figure;
        Square(std::initializer_list<Point*> t);

        friend std::istream& operator>>(std::istream& in, Square &square);
};