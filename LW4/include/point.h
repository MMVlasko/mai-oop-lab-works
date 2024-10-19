#pragma once

#include <iostream>
#include <cmath>

template <class T> class Point {
    public:
        T x, y;

    public:
        Point();

        Point(T x, T y);

        Point(const Point &other);

        Point(Point &&other) noexcept;

        Point &operator=(const Point &other);

        Point &operator=(Point &&other) noexcept;

        bool operator==(const Point &other) const;

        bool operator!=(const Point &other) const;

        double distance(const Point &other) const;

        template <class U>
        friend std::ostream& operator<<(std::ostream &os, const Point<U> &point);
};


template <class T>
Point<T>::Point() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}

template <class T>
Point<T>::Point(const T x, const T y) : x(x), y(y) {}

template <class T>
Point<T>::Point(const Point &other) = default;

template <class T>
Point<T>::Point(Point &&other) noexcept : x(other.x), y(other.y) {}

template <class T>
Point<T>& Point<T>::operator=(const Point &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template <class T>
Point<T>& Point<T>::operator=(Point &&other) noexcept {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template <class T>
bool Point<T>::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

template <class T>
bool Point<T>::operator!=(const Point &other) const {
    return x != other.x || y != other.y;
}

template <class T>
double Point<T>::distance(const Point &other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

template <class T>
std::ostream& operator<<(std::ostream &os, const Point<T> &point) {
    os << '(' << point.x << ", " << point.y << ')';
    return os;
}