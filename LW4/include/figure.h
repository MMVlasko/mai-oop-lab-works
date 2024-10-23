#pragma once

#include <initializer_list>

#include "array.h"
#include "point.h"
#include "tools.h"

template <Scalar T> class Figure {
    protected:
        std::shared_ptr<Array<Point<T>>> _crds;
        std::string _name;

    public:
        Figure();
        
        Figure(std::initializer_list<Point<T>> t);

        Figure(const Figure &other);

        Figure(Figure &&other) noexcept;

        virtual ~Figure() = default;

        Figure &operator=(const Figure &other);

        Figure &operator=(Figure &&other) noexcept;

        bool operator==(const Figure &other) const;

        bool operator!=(const Figure &other) const;

        template <Scalar U>
        friend std::ostream& operator<<(std::ostream &os, const Figure<U> &figure);

        std::shared_ptr<Array<Point<T>>> get_crds_array() const;

        std::string get_name();

        std::shared_ptr<Point<T>> get_center() const;

        explicit operator double() const;

        template <Scalar U>
        friend std::istream& operator>>(std::istream& in, Figure<U>& figure);
};


template <Scalar T>
Figure<T>::Figure() {
    _name = "uninitialized";
    _crds = nullptr;
}

template <Scalar T>
Figure<T>::Figure(const std::initializer_list<Point<T>> t) {
    _name = "Figure";
    auto crds = Array<Point<T>>();
    for (Point<T> point: t)
        crds.add(point);
    _crds = sort_points<T>(crds);
}

template <Scalar T>
Figure<T>::Figure(const Figure &other) {
    _name = "Figure";
    _crds = std::make_shared<Array<Point<T>>>(Array(*other._crds));
}

template <Scalar T>
Figure<T>::Figure(Figure &&other) noexcept {
    _name = "Figure";
    _crds = other._crds;
    other._crds = nullptr;
}

template <Scalar T>
Figure<T>& Figure<T>::operator=(const Figure &other) {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    if (this != &other) {
        _name = other._name;
        _crds = std::make_shared<Array<Point<T>>>(Array(*other._crds));
    }
    return *this;
}

template <Scalar T>
Figure<T>& Figure<T>::operator=(Figure &&other) noexcept {
    if (this != &other && _crds != nullptr) {
        _name = other._name;
        _crds = other._crds;
        other._crds = nullptr;
    }
    return *this;
}

template <Scalar T>
bool Figure<T>::operator==(const Figure &other) const {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    if (other._crds->size == _crds->size) {
        for (int i = 0; i < _crds->size; ++i) {
            if (*(*other._crds)[i] != *(*_crds)[i])
                return false;
        }
        return true;
    }
    return false;
}

template <Scalar T>
bool Figure<T>::operator!=(const Figure &other) const {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    if (other._crds->size == _crds->size) {
        for (int i = 0; i < _crds->size; ++i) {
            if (*(*other._crds)[i] != *(*_crds)[i])
                return false;
        }
        return false;
    }
    return true;
}

template <Scalar T>
std::ostream& operator<<(std::ostream &os, const Figure<T> &figure) {
    if (figure._crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    os << figure._name << " " << *figure._crds;
    return os;
}

template <Scalar T>
std::shared_ptr<Array<Point<T>>> Figure<T>::get_crds_array() const {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    return std::make_shared<Array<Point<T>>>(Array<Point<T>>(*_crds));
}

template <Scalar T>
std::string Figure<T>::get_name() {
    return _name;
}

template <Scalar T>
std::shared_ptr<Point<T>> Figure<T>::get_center() const {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    auto tr_centers = Array<Point<T>>();
    for (int i = 0; i < _crds->size - 2; ++i)
        tr_centers.add(Point(static_cast<T>(((*_crds)[0]->x + (*_crds)[i + 1]->x + (*_crds)[i + 2]->x) / 3.0),
            static_cast<T>(((*_crds)[0]->y + (*_crds)[i + 1]->y + (*_crds)[i + 2]->y) / 3.0)));

    auto result = Point<T>();

    for (int i = 0; i < tr_centers.size; ++i) {
        result.x += tr_centers[i]->x;
        result.y += tr_centers[i]->y;
    }
    result.x /= static_cast<double>(tr_centers.size);
    result.y /= static_cast<double>(tr_centers.size);

    return std::make_shared<Point<T>>(result);
}

template <Scalar T>
Figure<T>::operator double() const {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    return get_square<T>(*_crds);
}

template <Scalar T>
std::istream& operator>>(std::istream& in, Figure<T>& figure) {
    throw NotImplementedException("Input not implemented");
}