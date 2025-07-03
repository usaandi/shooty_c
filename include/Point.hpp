#ifndef POINT_HPP
#define POINT_HPP


class Point {
public:
    double x = 0;
    double y = 0;

public:
    // Constructors
    Point() { };

    Point(double a, double b) :
        x(a),
        y(b)
    {} 

    // Overload the + operator
    Point operator+(const Point& rhs) const;
    // Overload the += operator
    Point& operator+=(const Point& rhs);


};

#endif // POINT_HPP