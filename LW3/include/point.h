#pragma once

#include <iostream>

class Point {
    public:
        double x, y;

    public:
        Point();

        Point(double x, double y);

        Point(const Point &other);

        Point(Point &&other) noexcept;

        Point &operator=(const Point &other);

        Point &operator=(Point &&other) noexcept;

        bool operator==(Point &other);

        bool operator!=(Point &other);

        double distance(Point &other);

        friend std::ostream& operator<<(std::ostream &os, Point &point);
};