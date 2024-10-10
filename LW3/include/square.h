#pragma once

#include "figure.h"

class Square : public Figure {
    public:
        Square(std::initializer_list<Point*> t);
};