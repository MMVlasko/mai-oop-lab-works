#include <square.h>
#include <tools.h>

Square::Square(std::initializer_list<Point*> t) {
    if (t.size() != 4)
        throw BadInputDataException("Expected four points");
    
    Array<Point> crds = Array<Point>();
    for (Point* point: t)
        crds.add(point);
    _crds = sort_points(crds);

    auto p0 = (*_crds)[0];
    auto p1 = (*_crds)[1];
    auto p2 = (*_crds)[2];
    auto p3 = (*_crds)[3];

    bool right_angle = ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    double length = p0->distance(*p1);
    for (int i = 2; i < _crds->size; ++i)
        if ((*_crds)[i - 1]->distance(*(*_crds)[i]) != length || !right_angle) {
            _crds->free_elements();
            delete _crds;
            _crds = nullptr;
            throw BadInputDataException("Lengths of sides not equal");
        }

    _name = "Square";
}

std::istream& operator>>(std::istream& in, Square& square) {
    Point *first_point = new Point();
    in >> first_point->x >> first_point->y;
    check_cin();

    Point *second_point = new Point();
    in >> second_point->x >> second_point->y;
    check_cin();

    Point *third_point = new Point();
    in >> third_point->x >> third_point->y;
    check_cin();

    Point *fourth_point = new Point();
    in >> fourth_point->x >> fourth_point->y;
    check_cin();

    Array<Point> crds = Array<Point>({first_point, second_point, third_point, fourth_point});
    square._crds = sort_points(crds);

    auto p0 = (*square._crds)[0];
    auto p1 = (*square._crds)[1];
    auto p2 = (*square._crds)[2];
    auto p3 = (*square._crds)[3];

    bool right_angle = ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    double length = p0->distance(*p1);
    for (int i = 2; i < square._crds->size; ++i)
        if ((*square._crds)[i - 1]->distance(*(*square._crds)[i]) != length || !right_angle) {
            square._crds->free_elements();
            delete square._crds;
            square._crds = nullptr;
            throw BadInputDataException("Lengths of sides not equal");
        }

    square._name = "Square";

    return in;
}