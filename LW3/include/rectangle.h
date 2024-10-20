#pragma once

#include "figure.h"

class Rectangle final : public Figure {
    public:
        Rectangle() = default;
        Rectangle(std::initializer_list<Point*> t);

        friend std::istream& operator>>(std::istream& in, Rectangle &rectangle);
};