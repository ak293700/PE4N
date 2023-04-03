#pragma once

#include "../Vec3/Vec3.h"
#include "optional"
#include "../Triangle/Triangle.h"

struct Plane {
    Vec3 p; // point that exists on the plane
    Vec3 normal; // normal vector of the plane, must be normalized

    Plane(Vec3 p, Vec3 normal) : p(p), normal(normal.normalize())
    {}

    //// return the point the line intersects with the plane
    //// The line is represented by the two points a and b
    [[nodiscard]] Vec3 GetIntersectionPoint(const Vec3& a, const Vec3& b) const;

    int TriangleClipAgainstPlane(const Triangle& in, Triangle& out1, Triangle& out2) const;
};