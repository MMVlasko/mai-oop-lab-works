#include <iostream>

#include <figure.h>
#include <tools.h>

Figure::Figure() {
    _name = "uninitialized";
    _crds = nullptr;
}

Figure::Figure(const std::initializer_list<Point*> t) {
    _name = "Figure";
    auto crds = Array<Point>();
    for (Point* point: t)
        crds.add(point);
    _crds = sort_points(crds);
}

Figure::Figure(const Figure &other) {
    _name = "Figure";
    _crds = new Array(*other._crds);
}

Figure::Figure(Figure &&other) noexcept {
    _name = "Figure";
    _crds = other._crds;
    other._crds = nullptr;
}

Figure::~Figure() noexcept {
    if (_crds != nullptr) {
        _crds->free_elements();
        delete _crds;
    }
}

Figure& Figure::operator=(const Figure &other) {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    if (this != &other) {
        _crds->free_elements();
        delete _crds;

        _name = other._name;
        _crds = new Array(*other._crds);
    }
    return *this;
}

Figure& Figure::operator=(Figure &&other) noexcept {
    if (this != &other && _crds != nullptr) {
        _crds->free_elements();
        delete _crds;

        _name = other._name;
        _crds = other._crds;
        other._crds = nullptr;
    }
    return *this;
}

bool Figure::operator==(const Figure &other) const {
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

bool Figure::operator!=(const Figure &other) const {
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

std::ostream& operator<<(std::ostream &os, const Figure &figure) {
    if (figure._crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    os << figure._name << " " << *figure._crds;
    return os;
}

Array<Point> *Figure::get_crds_array() const {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    return new Array(*_crds);
}

std::string Figure::get_name() {
    return _name;
}

Point* Figure::get_center() const {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    auto tr_centers = Array<Point>();
    for (int i = 0; i < _crds->size - 2; ++i)
        tr_centers.add(new Point(((*_crds)[0]->x + (*_crds)[i + 1]->x + (*_crds)[i + 2]->x) / 3.0,
            ((*_crds)[0]->y + (*_crds)[i + 1]->y + (*_crds)[i + 2]->y) / 3.0));

    auto *result = new Point();

    for (int i = 0; i < tr_centers.size; ++i) {
        result->x += tr_centers[i]->x;
        result->y += tr_centers[i]->y;
    }
    result->x /= static_cast<double>(tr_centers.size);
    result->y /= static_cast<double>(tr_centers.size);

    return result;
}

Figure::operator double() const {
    if (_crds == nullptr)
        throw UninitializedException("Figure must be initialized with >>");

    return get_square(*_crds);
}

std::istream& operator>>(std::istream& in, Figure& figure) {
    throw NotImplementedException("Input not implemented");
}