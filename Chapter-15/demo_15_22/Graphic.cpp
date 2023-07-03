#include <cmath>
#include "Graphic.h"

double circle::get_area() const
{
    return get_radius() * get_radius() * PI;
}

double rectangle::get_area() const
{
    return get_length() * get_width();
}

double sphere::get_area() const
{
    return 4.0 * PI * radius * radius;
}

double sphere::get_volumn() const
{
    return (4.0 / 3) * PI * radius * radius * radius;
}

double cone::get_area() const
{
    return PI * radius * radius + PI * radius * busbar;
}

double cone::get_volumn() const
{
    double height = sqrt(busbar * busbar - radius * radius);
	return PI * radius * radius * height / 3; 
}