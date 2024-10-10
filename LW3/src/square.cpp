#include <square.h>
#include <tools.h>

Square::Square(std::initializer_list<Point*> t) {
    if (t.size() != 4)
        throw BadInputDataException("Expected four points");
    
    Array<Point> crds = Array<Point>();
    for (Point* point: t)
        crds.add(point);
    _crds = sort_points(crds);

    double length = (*_crds)[0]->distance(*(*_crds)[1]);
    for (int i = 2; i < _crds->size; ++i)
        if ((*_crds)[i - 1]->distance(*(*_crds)[i]) != length) {
            _crds->free_elements();
            delete _crds;
            throw BadInputDataException("Lengths of sides not equal");
        }

    _name = "Square";
}