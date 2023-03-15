#include "Vec3.h"
#include <iostream>
#import <math.h>

Vec3 Vec3::CrossProduct(const Vec3 &other) const
{
    return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
    };
}

float Vec3::DotProduct(const Vec3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::Diff(const Vec3 &other) const
{
    return {
            other.x - x,
            other.y - y,
            other.z - z,
    };
}

void Vec3::Print() const
{
    std::cout << '(' << x << ", " << y << ", " << z << ')' << '\n';
}

float Vec3::Length() const
{
    return sqrt(x * x + y * y + z * z);
}

void Vec3::Normalize()
{
    float length = Length();
    if (length == 0)
        return;

    x /= length;
    y /= length;
    z /= length;
}
