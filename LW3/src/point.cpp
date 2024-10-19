#include <cmath>

#include <point.h>

Point::Point() : x(0.), y(0.) {}

Point::Point(const double x, const double y) : x(x), y(y) {}

Point::Point(const Point &other) = default;

Point::Point(Point &&other) noexcept : x(other.x), y(other.y) {}

Point& Point::operator=(const Point &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

Point& Point::operator=(Point &&other) noexcept {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

bool Point::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point &other) const {
    return x != other.x || y != other.y;
}

double Point::distance(const Point &other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

std::ostream& operator<<(std::ostream &os, const Point &point) {
    os << '(' << point.x << ", " << point.y << ')';
    return os;
}