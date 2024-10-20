#pragma once

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

        bool operator==(const Point &other) const;

        bool operator!=(const Point &other) const;

        double distance(const Point &other) const;

        friend std::ostream& operator<<(std::ostream &os, const Point &point);
};