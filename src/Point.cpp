#include "Point.hpp"

Point Point::operator+(const Point& rhs) const  
{
    return Point(x + rhs.x, y + rhs.y);
}

Point& Point::operator+=(const Point& rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}