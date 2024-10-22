#pragma once

#include "array.h"
#include "point.h"

template <Scalar T>
std::shared_ptr<Array<Point<T>>> sort_points(Array<Point<T>> &points) {
    auto crds = Array(points);
    auto res = std::make_shared<Array<Point<T>>>(Array<Point<T>>());

    auto _min = crds[0];
    int min_i = 0;

    for (int i = 0; i < crds.size; ++i)
        if (crds[i]->y < _min->y || (crds[i]->y == _min->y && crds[i]->x < _min->x)) {
            _min = crds[i];
            min_i = i;
        }

    res->add(*crds.pop(min_i));

    while (crds.size) {
        auto min_point = crds[0];
        double min = 10.;
        min_i = 0;

        for (int i = 0; i < crds.size; ++i) {
            double angle = std::atan2(crds[i]->y - (*res)[0]->y, crds[i]->x - (*res)[0]->x);
            if (angle < min || (angle == min && crds[i]->y < min_point->y)) {
                min = angle;
                min_point = crds[i];
                min_i = i;
            }
        }
        res->add(*crds.pop(min_i));
    }
    return res;
}

template <Scalar T>
T get_square(Array<Point<T>> &points) {
    T square = static_cast<T>(0);

    for (int i = 0; i < points.size - 1; ++i)
        square += (points[i]->x * (points[i + 1]->y - points[i - 1]->y));

    square += (points[points.size - 1]->x * (points[0]->y - points[points.size - 2]->y));
    square = std::abs(square);
    square /= 2;

    return square;
}

void check_cin();