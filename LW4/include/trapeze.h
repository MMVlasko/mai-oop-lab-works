#pragma once

#include "tools.h"
#include "figure.h"

template <Scalar T> class Trapeze : public Figure<T> {
    public:
        using Figure<T>::Figure;
        Trapeze(std::initializer_list<Point<T>> t);

        template <Scalar U>
        friend std::istream& operator>>(std::istream& in, Trapeze<U> &trapeze);
};


template <Scalar T>
Trapeze<T>::Trapeze(std::initializer_list<Point<T>> t) {
    if (t.size() != 4)
        throw BadInputDataException("Expected four points");

    auto crds = Array<Point<T>>();
    for (Point<T> point: t)
        crds.add(point);
    this->_crds = sort_points<T>(crds);

    const auto p0 = (*this->_crds)[0];
    const auto p1 = (*this->_crds)[1];
    const auto p2 = (*this->_crds)[2];
    const auto p3 = (*this->_crds)[3];

    auto first_dif_x = std::abs(p1->x - p0->x);
    auto sec_dif_x = std::abs(p2->x - p3->x);
    auto first_dif_y = std::abs(p1->y - p0->y);
    auto sec_dif_y = std::abs(p2->y - p3->y);

    auto third_dif_x = std::abs(p1->x - p2->x);
    auto fourth_dif_x = std::abs(p3->x - p0->x);
    auto third_dif_y = std::abs(p2->y - p1->y);
    auto fourth_dif_y = std::abs(p3->y - p0->y);

    bool is_trapeze = first_dif_x / sec_dif_x == first_dif_y / sec_dif_y ||
            third_dif_x / fourth_dif_x == third_dif_y / fourth_dif_y || (first_dif_x == 0. && sec_dif_x == 0.) ||
            (first_dif_y == 0. && sec_dif_y == 0.) || (third_dif_x == 0. && fourth_dif_x == 0.) ||
            (third_dif_y == 0. && fourth_dif_y == 0.);

    if (!is_trapeze || !get_square(*this->_crds))
        throw BadInputDataException("Non-parallel sides!");

    this->_name = "Trapeze";
}

template <Scalar T>
std::istream& operator>>(std::istream& in, Trapeze<T>& trapeze) {
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
    trapeze._crds = sort_points<T>(crds);

    const auto p0 = (*trapeze._crds)[0];
    const auto p1 = (*trapeze._crds)[1];
    const auto p2 = (*trapeze._crds)[2];
    const auto p3 = (*trapeze._crds)[3];

    auto first_dif_x = std::abs(p1->x - p0->x);
    auto sec_dif_x = std::abs(p2->x - p3->x);
    auto first_dif_y = std::abs(p1->y - p0->y);
    auto sec_dif_y = std::abs(p2->y - p3->y);

    auto third_dif_x = std::abs(p1->x - p2->x);
    auto fourth_dif_x = std::abs(p3->x - p0->x);
    auto third_dif_y = std::abs(p2->y - p1->y);
    auto fourth_dif_y = std::abs(p3->y - p0->y);

    bool is_trapeze = first_dif_x / sec_dif_x == first_dif_y / sec_dif_y ||
            third_dif_x / fourth_dif_x == third_dif_y / fourth_dif_y || (first_dif_x == 0. && sec_dif_x == 0.) ||
            (first_dif_y == 0. && sec_dif_y == 0.) || (third_dif_x == 0. && fourth_dif_x == 0.) ||
            (third_dif_y == 0. && fourth_dif_y == 0.);

    if (!is_trapeze || !get_square(*trapeze._crds))
        throw BadInputDataException("Lengths of sides not equal");

    trapeze._name = "Trapeze";

    return in;
}