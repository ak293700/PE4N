#include "Triangle.h"

Vec3 Triangle::norm() const
{
    Vec3 line1 = a.Diff(b);
    Vec3 line2 = a.Diff(c);

    return line1.CrossProduct(line2);
}
