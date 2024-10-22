#include <iostream>

#include <rectangle.h>
#include <tools.h>

Rectangle::Rectangle(const std::initializer_list<Point*> t) {
    if (t.size() != 4)
        throw BadInputDataException("Expected four points");

    auto crds = Array<Point>();
    for (Point* point: t)
        crds.add(point);
    _crds = sort_points(crds);

    const auto p0 = (*_crds)[0];
    const auto p1 = (*_crds)[1];
    const auto p2 = (*_crds)[2];
    const auto p3 = (*_crds)[3];

    bool is_rectangle = p0->distance(*p1) == p2->distance(*p3) && p1->distance(*p2) == p3->distance(*p0);
    is_rectangle &= ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    
    if (!is_rectangle) {
        _crds->free_elements();
        delete _crds;
        _crds = nullptr;
        throw BadInputDataException("Figure is not rectangle");
    }

    _name = "Rectangle";
}

std::istream& operator>>(std::istream& in, Rectangle& rectangle) {
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
    rectangle._crds = sort_points(crds);

    const auto p0 = (*rectangle._crds)[0];
    const auto p1 = (*rectangle._crds)[1];
    const auto p2 = (*rectangle._crds)[2];
    const auto p3 = (*rectangle._crds)[3];

    bool is_rectangle = p0->distance(*p1) == p2->distance(*p3) && p1->distance(*p2) == p3->distance(*p0);
    is_rectangle &= ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    
    if (!is_rectangle) {
        rectangle._crds->free_elements();
        delete rectangle._crds;
        rectangle._crds = nullptr;
        throw BadInputDataException("Figure is not rectangle");
    }

    rectangle._name = "Rectangle";

    return in;
}