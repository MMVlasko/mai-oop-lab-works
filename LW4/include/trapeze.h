#pragma once

#include "figure.h"

class Trapeze final : public Figure {
    public:
        Trapeze() = default;
        Trapeze(std::initializer_list<Point*> t);

        friend std::istream& operator>>(std::istream& in, Trapeze &trapeze);
};