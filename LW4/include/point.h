#pragma once

#include <cmath>
#include <type_traits>

template <class T>
concept Scalar = std::is_scalar_v<T>;

template <Scalar T> class Point {
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


template <Scalar T>
Point<T>::Point() : x(static_cast<T>(0)), y(static_cast<T>(0)) {}

template <Scalar T>
Point<T>::Point(const T x, const T y) : x(x), y(y) {}

template <Scalar T>
Point<T>::Point(const Point &other) = default;

template <Scalar T>
Point<T>::Point(Point &&other) noexcept = default;

template <Scalar T>
Point<T>& Point<T>::operator=(const Point &other) = default;

template <Scalar T>
Point<T>& Point<T>::operator=(Point &&other) noexcept = default;

template <Scalar T>
bool Point<T>::operator==(const Point &other) const {
    return x == other.x && y == other.y;
}

template <Scalar T>
bool Point<T>::operator!=(const Point &other) const {
    return x != other.x || y != other.y;
}

template <Scalar T>
double Point<T>::distance(const Point &other) const {
    return std::sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
}

template <Scalar T>
std::ostream& operator<<(std::ostream &os, const Point<T> &point) {
    os << '(' << point.x << ", " << point.y << ')';
    return os;
}