#pragma once

#include "array.h"

class Figure {
    private:
        Array<double> *_crds;

    public:
        Figure();

        Figure(const Figure &other);

        Figure(Figure &&other) noexcept;

        Figure &operator=(const Figure &other);

        Figure &operator=(Figure &&other) noexcept;
};

