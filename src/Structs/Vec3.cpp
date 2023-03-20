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

Vec3 Vec3::Normalize() const
{
    float length = Length();
    if (length == 0)
        return {0, 0, 0};

    return {
            x / length,
            y / length,
            z / length
    };
}

Vec3 Vec3::operator+(const Vec3 &other) const
{
    return {
            x + other.x,
            y + other.y,
            z + other.z
    };
}

Vec3 Vec3::operator-(const Vec3 &other) const
{
    return {
            x - other.x,
            y - other.y,
            z - other.z
    };
}

Vec3 Vec3::operator+(float other) const
{
    return {
            x + other,
            y + other,
            z + other
    };
}

Vec3 Vec3::operator-(float other) const
{
    return {
            x - other,
            y - other,
            z - other
    };
}

Vec3 Vec3::operator*(float other) const
{
    return {
            x * other,
            y * other,
            z * other
    };
}

Vec3 Vec3::operator/(float other) const
{
    return {
            x / other,
            y / other,
            z / other
    };
}

Vec3 Vec3::operator*(const Matrix4x4 &m) const
{
    Vec3 res = {
            x * m.get(0, 0) + y * m.get(1, 0) + z * m.get(2, 0) + m.get(3, 0),
            x * m.get(0, 1) + y * m.get(1, 1) + z * m.get(2, 1) + m.get(3, 1),
            x * m.get(0, 2) + y * m.get(1, 2) + z * m.get(2, 2) + m.get(3, 2)
    };

    float w = x * m.get(0, 3)
              + y * m.get(1, 3)
              + z * m.get(2, 3)
              + m.get(3, 3);

    if (w != 0.0f)
    {
        res.x /= w;
        res.y /= w;
        res.z /= w;
    }

    return res;
}

Vec3 Vec3::operator+=(const Vec3 &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3 Vec3::operator-=(const Vec3 &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}
