#pragma once

#include "tools.h"
#include "figure.h"

template <Scalar T> class Square : public Figure<T> {
    public:
        using Figure<T>::Figure;
        Square(std::initializer_list<Point<T>> t);

        template <Scalar U>
        friend std::istream& operator>>(std::istream& in, Square<U> &square);
};


template <Scalar T>
Square<T>::Square(const std::initializer_list<Point<T>> t) {
    if (t.size() != 4)
        throw BadInputDataException("Expected four points");

    auto crds = Array<Point<T>>();
    for (Point<T> point: t)
        crds.add(point);
    this->_crds = sort_points(crds);

    const auto p0 = (*this->_crds)[0];
    const auto p1 = (*this->_crds)[1];
    const auto p3 = (*this->_crds)[3];

    const bool right_angle = ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    const double length = p0->distance(*p1);

    for (int i = 2; i < this->_crds->size; ++i)
        if ((*this->_crds)[i - 1]->distance(*(*this->_crds)[i]) != length || !right_angle)
            throw BadInputDataException("Lengths of sides not equal");

    this->_name = "Square";
}

template <Scalar T>
std::istream& operator>>(std::istream& in, Square<T>& square) {
    auto first_point = Point<T>();
    in >> first_point.x >> first_point.y;
    check_cin();

    auto second_point = Point<T>();
    in >> second_point.x >> second_point.y;
    check_cin();

    auto third_point = Point<T>();
    in >> third_point.x >> third_point.y;
    check_cin();

    auto fourth_point = Point<T>();
    in >> fourth_point.x >> fourth_point.y;
    check_cin();

    auto crds = Array({first_point, second_point, third_point, fourth_point});
    square._crds = sort_points(crds);

    const auto p0 = (*square._crds)[0];
    const auto p1 = (*square._crds)[1];
    const auto p3 = (*square._crds)[3];

    const bool right_angle = ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    const double length = p0->distance(*p1);
    for (int i = 2; i < square._crds->size; ++i)
        if ((*square._crds)[i - 1]->distance(*(*square._crds)[i]) != length || !right_angle)
            throw BadInputDataException("Lengths of sides not equal");

    square._name = "Square";

    return in;
}