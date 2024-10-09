#include <iostream>

#include <figure.h>

Figure::Figure(std::initializer_list<Point*> t) {
    _crds = new Array<Point>();
    for (Point* point: t)
        _crds->add(point);
}

Figure::~Figure() noexcept {
    _crds->free_elements();
    delete _crds;
}

bool Figure::operator==(Figure &other)  {
    if (other._crds->size == _crds->size) {
        for (int i = 0; i < _crds->size; ++i) {
            bool flag = false;
            for (int j = 0; j < _crds->size; ++j)
                if (*(*_crds)[i] == *(*other._crds)[j]) {
                    flag = true;
                    break;
                }
            if (!flag)
                return false;
        }
        return true;
    }
    return false;
}

bool Figure::operator!=(Figure &other)  {
    if (other._crds->size == _crds->size) {
        for (int i = 0; i < _crds->size; ++i) {
            bool flag = false;
            for (int j = 0; j < _crds->size; j++)
                if (_crds[i] == other._crds[j]) {
                    flag = true;
                    break;
                }
            if (!flag)
                return true;
        }
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream &os, Figure &figure) {
    os << *figure._crds;
    return os;
}

Array<Point> *Figure::get_crds_array() {
    return new Array<Point>(*_crds);
}

Figure::Figure(const Figure &other) {
    _crds = new Array<Point>(*other._crds);
}

Figure::Figure(Figure &&other) noexcept {
    _crds = other._crds;
    other._crds = nullptr;
}