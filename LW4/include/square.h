#pragma once

#include "figure.h"

class Square final : public Figure {
    public:
        Square() = default;
        Square(std::initializer_list<Point*> t);

        friend std::istream& operator>>(std::istream& in, Square &square);
};