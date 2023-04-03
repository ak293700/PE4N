#include "Triangle.h"
#include <iostream>

Vec3 Triangle::norm() const
{
    Vec3 line1 = a.diff(b);
    Vec3 line2 = a.diff(c);

    return line1.cross(line2);
}

void Triangle::print() const {
    std::cout << "a: ";
    a.print();

    std::cout << "b: ";
    b.print();

    std::cout << "c: ";
    c.print();
}
