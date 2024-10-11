#pragma once

#include "figure.h"

class Trapeze : public Figure {
    public:
        Trapeze() : Figure() {}
        Trapeze(std::initializer_list<Point*> t);

        friend std::istream& operator>>(std::istream& in, Trapeze &trapeze);
};