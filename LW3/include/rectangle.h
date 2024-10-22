#pragma once

#include "figure.h"

class Rectangle : public Figure {
    public:
        using  Figure::Figure;
        Rectangle(std::initializer_list<Point*> t);

        friend std::istream& operator>>(std::istream& in, Rectangle &rectangle);
};