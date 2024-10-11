#include <rectangle.h>
#include <tools.h>

Rectangle::Rectangle(std::initializer_list<Point*> t) {
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

    bool is_rectangle = p0->distance(*p1) == p2->distance(*p3) && p1->distance(*p2) == p3->distance(*p0);
    is_rectangle &= ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    
    if (!is_rectangle) {
        _crds->free_elements();
            delete _crds;
            _crds = nullptr;
            throw BadInputDataException("Lengths of sides not equal");
    }

    _name = "Rectangle";
}

std::istream& operator>>(std::istream& in, Rectangle& rectangle) {
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
    rectangle._crds = sort_points(crds);

    auto p0 = (*rectangle._crds)[0];
    auto p1 = (*rectangle._crds)[1];
    auto p2 = (*rectangle._crds)[2];
    auto p3 = (*rectangle._crds)[3];

    bool is_rectangle = p0->distance(*p1) == p2->distance(*p3) && p1->distance(*p2) == p3->distance(*p0);
    is_rectangle &= ((p3->x - p0->x) * (p1->x - p0->x) + (p3->y - p0->y) * (p1->y - p0->y) == 0.);
    
    if (!is_rectangle) {
        rectangle._crds->free_elements();
            delete rectangle._crds;
            rectangle._crds = nullptr;
            throw BadInputDataException("Lengths of sides not equal");
    }

    rectangle._name = "Rectangle";

    return in;
}