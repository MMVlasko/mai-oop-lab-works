#pragma once

#include <initializer_list>

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

        bool operator==(const Figure &other) const;

        bool operator!=(const Figure &other) const;

        friend std::ostream& operator<<(std::ostream &os, const Figure &figure);

        Array<Point> *get_crds_array() const;

        std::string get_name();

        Point *get_center() const;

        explicit operator double() const;

        friend std::istream& operator>>(std::istream& in, Figure& figure);
};
