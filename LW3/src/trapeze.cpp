#include <iostream>

#include <trapeze.h>
#include <tools.h>

Trapeze::Trapeze(const std::initializer_list<Point*> t) {
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

    auto first_dif_x = std::abs(p1->x - p0->x);
    auto sec_dif_x = std::abs(p2->x - p3->x);
    auto first_dif_y = std::abs(p1->y - p0->y);
    auto sec_dif_y = std::abs(p2->y - p3->y);

    auto third_dif_x = std::abs(p1->x - p2->x);
    auto fourth_dif_x = std::abs(p3->x - p0->x);
    auto third_dif_y = std::abs(p2->y - p1->y);
    auto fourth_dif_y = std::abs(p3->y - p0->y);


    bool is_trapeze = first_dif_x / sec_dif_x == first_dif_y / sec_dif_y ||
            third_dif_x / fourth_dif_x == third_dif_y / fourth_dif_y || (first_dif_x == 0. && sec_dif_x == 0.) ||
            (first_dif_y == 0. && sec_dif_y == 0.) || (third_dif_x == 0. && fourth_dif_x == 0.) ||
            (third_dif_y == 0. && fourth_dif_y == 0.);


    if (!is_trapeze) {
        _crds->free_elements();
        delete _crds;
        _crds = nullptr;
        throw BadInputDataException("Figure is not trapeze");
    }

    _name = "Trapeze";
}

std::istream& operator>>(std::istream& in, Trapeze& trapeze) {
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
    trapeze._crds = sort_points(crds);

    const auto p0 = (*trapeze._crds)[0];
    const auto p1 = (*trapeze._crds)[1];
    const auto p2 = (*trapeze._crds)[2];
    const auto p3 = (*trapeze._crds)[3];

    auto first_dif_x = std::abs(p1->x - p0->x);
    auto sec_dif_x = std::abs(p2->x - p3->x);
    auto first_dif_y = std::abs(p1->y - p0->y);
    auto sec_dif_y = std::abs(p2->y - p3->y);

    auto third_dif_x = std::abs(p1->x - p2->x);
    auto fourth_dif_x = std::abs(p3->x - p0->x);
    auto third_dif_y = std::abs(p2->y - p1->y);
    auto fourth_dif_y = std::abs(p3->y - p0->y);


    bool is_trapeze = first_dif_x / sec_dif_x == first_dif_y / sec_dif_y ||
            third_dif_x / fourth_dif_x == third_dif_y / fourth_dif_y || (first_dif_x == 0. && sec_dif_x == 0.) ||
            (first_dif_y == 0. && sec_dif_y == 0.) || (third_dif_x == 0. && fourth_dif_x == 0.) || 
            (third_dif_y == 0. && fourth_dif_y == 0.);
    
    if (!is_trapeze) {
        trapeze._crds->free_elements();
        delete trapeze._crds;
        trapeze._crds = nullptr;
        throw BadInputDataException("Figure is not trapeze");
    }

    trapeze._name = "Trapeze";

    return in;
}