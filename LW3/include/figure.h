#pragma once

#include <initializer_list>
#include <iostream>

#include "array.h"
#include "point.h"

class Figure {
    protected:
        Array<Point> *_crds;
        std::string _name;

    public:
        Figure();
        
        Figure(std::initializer_list<Point*> t);

        Figure(const Figure &other);

        Figure(Figure &&other) noexcept;

        virtual ~Figure() noexcept;

        Figure &operator=(const Figure &other);

        Figure &operator=(Figure &&other) noexcept;

        bool operator==(Figure &other);

        bool operator!=(Figure &other);

        friend std::ostream& operator<<(std::ostream &os, Figure &figure);

        Array<Point> *get_crds_array();

        std::string get_name();

        Point *get_center();

        operator double() const;

        friend std::istream& operator>>(std::istream& in, Figure& figure);
};
