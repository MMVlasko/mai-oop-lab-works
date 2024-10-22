#include <iostream>

#include <square.h>
#include <tools.h>

Square::Square(const std::initializer_list<Point*> t) {
    if (t.size() != 4)
        throw BadInputDataException("Expected four points");

    auto crds = Array<Point>();
    for (Point* point: t)
        crds.add(point);
    _crds = sort_points(crds);

    const auto p0 = (*_crds)[0];
    const auto p1 = (*_crds)[1];
    const auto p3 = (*_crds)[3];

    const bool right_angle = ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    const double length = p0->distance(*p1);

    for (int i = 2; i < _crds->size; ++i)
        if ((*_crds)[i - 1]->distance(*(*_crds)[i]) != length || !right_angle) {
            _crds->free_elements();
            delete _crds;
            _crds = nullptr;
            throw BadInputDataException("Figure is not square");
        }

    _name = "Square";
}

std::istream& operator>>(std::istream& in, Square& square) {
    auto *first_point = new Point();
    in >> first_point->x >> first_point->y;
    check_cin();

    auto *second_point = new Point();
    in >> second_point->x >> second_point->y;
    check_cin();

    auto *third_point = new Point();
    in >> third_point->x >> third_point->y;
    check_cin();

    auto *fourth_point = new Point();
    in >> fourth_point->x >> fourth_point->y;
    check_cin();

    auto crds = Array({first_point, second_point, third_point, fourth_point});
    square._crds = sort_points(crds);

    const auto p0 = (*square._crds)[0];
    const auto p1 = (*square._crds)[1];
    const auto p3 = (*square._crds)[3];

    const bool right_angle = ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    const double length = p0->distance(*p1);
    for (int i = 2; i < square._crds->size; ++i)
        if ((*square._crds)[i - 1]->distance(*(*square._crds)[i]) != length || !right_angle) {
            square._crds->free_elements();
            delete square._crds;
            square._crds = nullptr;
            throw BadInputDataException("Figure is not square");
        }

    square._name = "Square";

    return in;
}