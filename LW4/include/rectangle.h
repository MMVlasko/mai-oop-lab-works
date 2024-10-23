#pragma once

#include "tools.h"
#include "figure.h"

template <Scalar T> class Rectangle : public Figure<T> {
    public:
        using Figure<T>::Figure;
        Rectangle(std::initializer_list<Point<T>> t);

        template <Scalar U>
        friend std::istream& operator>>(std::istream& in, Rectangle<U> &rectangle);
};


template <Scalar T>
Rectangle<T>::Rectangle(const std::initializer_list<Point<T>> t) {
    if (t.size() != 4)
        throw BadInputDataException("Expected four points");

    auto crds = Array<Point<T>>();
    for (Point<T> point: t)
        crds.add(point);
    this->_crds = sort_points(crds);

    const auto p0 = (*this->_crds)[0];
    const auto p1 = (*this->_crds)[1];
    const auto p2 = (*this->_crds)[2];
    const auto p3 = (*this->_crds)[3];

    bool is_rectangle = p0->distance(*p1) == p2->distance(*p3) && p1->distance(*p2) == p3->distance(*p0);
    is_rectangle &= ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);

    if (!is_rectangle)
       throw BadInputDataException("Lengths of sides not equal");

    this->_name = "Rectangle";
}

template <Scalar T>
std::istream& operator>>(std::istream& in, Rectangle<T>& rectangle) {
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
    rectangle._crds = sort_points(crds);

    const auto p0 = (*rectangle._crds)[0];
    const auto p1 = (*rectangle._crds)[1];
    const auto p2 = (*rectangle._crds)[2];
    const auto p3 = (*rectangle._crds)[3];

    bool is_rectangle = p0->distance(*p1) == p2->distance(*p3) && p1->distance(*p2) == p3->distance(*p0);
    is_rectangle &= ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);

    if (!is_rectangle)
        throw BadInputDataException("Lengths of sides not equal");

    rectangle._name = "Rectangle";

    return in;
}