#include "Shape.h"

Shape::Shape() : _area(0), _perimeter(0)
{

}

float Shape::get_area(bool has_depth) const
{

	return _area;
}
