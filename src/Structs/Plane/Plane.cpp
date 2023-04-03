#include "Plane.h"
#include <iostream>

Vec3 Plane::GetIntersectionPoint(const Vec3 &a, const Vec3 &b) const {
    float planeDot = normal.dot(p);
    float aDot = a.dot(normal);
    float bDot = b.dot(normal);
    float t = (planeDot - aDot) / (bDot - aDot);
    return a + (b - a) * t;
}

//// return the number of points the triangle intersects with the plane
//// store in out1 and out2 the two triangles that could be generated
//// does not guarantee the vertex order to be clockwise
int Plane::TriangleClipAgainstPlane(const Triangle &in, Triangle &out1, Triangle &out2) const {
    // the signed distance from the point to the plane
    auto dist = [&](const Vec3 &v) -> float {
        return (normal.x * v.x + normal.y * v.y + normal.z * v.z - normal.dot(p));
    };

    const Vec3 *insidePoints[3]; // the points that are inside the plane
    const Vec3 *outsidePoints[3]; // the points that are outside the plane
    int insideCount = 0; // the number of points that are inside the plane
    int outsideCount = 0; // the number of points that are outside the plane

    // check the distance of each point of the in triangle from the plane
    float d0 = dist(in.a), d1 = dist(in.b), d2 = dist(in.c);

    // we add the points to the inside or outside array
    if (d0 >= 0)
        insidePoints[insideCount++] = &in.a;
    else
        outsidePoints[outsideCount++] = &in.a;

    if (d1 >= 0)
        insidePoints[insideCount++] = &in.b;
    else
        outsidePoints[outsideCount++] = &in.b;

    if (d2 >= 0)
        insidePoints[insideCount++] = &in.c;
    else
        outsidePoints[outsideCount++] = &in.c;

    // if all the points are outside the plane there is no output triangle
    if (insideCount == 0)
        return 0;

    // if all the points are inside the plane, the output triangle is the same as the input
    if (outsideCount == 0) {
        out1 = in;
        return 1;
    }

    // if there are one points inside the plane (two outsides) => 1 triangles
    // simply smaller the triangle
    if (insideCount == 1)
    {
        out1.a = *insidePoints[0];
        out1.b = GetIntersectionPoint(*insidePoints[0], *outsidePoints[0]);
        out1.c = GetIntersectionPoint(*insidePoints[0], *outsidePoints[1]);
        out1.texture = in.texture;
        return 1;
    }

    // if there are two points inside the plane (one outside) => 2 triangles
    // split the triangle in two
    out1.a = *insidePoints[0];
    out1.b = *insidePoints[1];
    out1.c = GetIntersectionPoint(*insidePoints[0], *outsidePoints[0]);
    out1.texture = in.texture;

    out2.a = *insidePoints[1];
    out2.b = GetIntersectionPoint(*insidePoints[1], *outsidePoints[0]);
    out2.c = out1.c;
    out2.texture = in.texture;

    return 2;
}
