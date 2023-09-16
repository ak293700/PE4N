#pragma once

#include "../Vec3/Vec3d.h"
#include "optional"
#include "../Triangle/Triangle.h"

struct Plane {
    Vec3d p; // point that exists on the plane
    Vec3d normal; // normal vector of the plane, must be normalized

    Plane() = default;
    Plane(Vec3d p, Vec3d normal) : p(p), normal(normal.normalize())
    {}

    //// return the point the line intersects with the plane
    //// The line is represented by the two points a and b
    [[nodiscard]] Vec3d GetIntersectionPoint(const Vec3d& a, const Vec3d& b) const;

    int TriangleClipAgainstPlane(const Triangle& in, Triangle& out1, Triangle& out2) const;
};