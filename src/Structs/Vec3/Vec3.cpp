#include "Vec3d.h"
#include <iostream>
#import <math.h>

Vec3d Vec3d::cross(const Vec3d &other) const
{
    return {
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
    };
}

float Vec3d::dot(const Vec3d &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vec3d Vec3d::diff(const Vec3d &other) const
{
    return {
            other.x - x,
            other.y - y,
            other.z - z,
    };
}

void Vec3d::print() const
{
    std::cout << '(' << x << ", " << y << ", " << z << ')' << '\n';
}

float Vec3d::diff() const
{
    return sqrt(x * x + y * y + z * z);
}

Vec3d Vec3d::normalize() const
{
    float length = diff();
    if (length == 0)
        return {0, 0, 0};

    return {
            x / length,
            y / length,
            z / length
    };
}

Vec3d Vec3d::operator+(const Vec3d &other) const
{
    return {
            x + other.x,
            y + other.y,
            z + other.z
    };
}

Vec3d Vec3d::operator-(const Vec3d &other) const
{
    return {
            x - other.x,
            y - other.y,
            z - other.z
    };
}

Vec3d Vec3d::operator+(float other) const
{
    return {
            x + other,
            y + other,
            z + other
    };
}

Vec3d Vec3d::operator-(float other) const
{
    return {
            x - other,
            y - other,
            z - other
    };
}

Vec3d Vec3d::operator*(float other) const
{
    return {
            x * other,
            y * other,
            z * other,
            w
    };
}

Vec3d Vec3d::operator/(float other) const
{
    return {
            x / other,
            y / other,
            z / other,
            w
    };
}

Vec3d Vec3d::operator*(const Matrix4x4 &m) const
{
    Vec3d res = {
            x * m.get(0, 0) + y * m.get(1, 0) + z * m.get(2, 0) + w * m.get(3, 0),
            x * m.get(0, 1) + y * m.get(1, 1) + z * m.get(2, 1) + w * m.get(3, 1),
            x * m.get(0, 2) + y * m.get(1, 2) + z * m.get(2, 2) + w * m.get(3, 2),
            x * m.get(0, 3) + y * m.get(1, 3) + z * m.get(2, 3) + w * m.get(3, 3)
    };

//    float w = x * m.get(0, 3)
//              + y * m.get(1, 3)
//              + z * m.get(2, 3)
//              + m.get(3, 3);
//
//    if (w != 0.0f)
//    {
//        res.x /= w;
//        res.y /= w;
//        res.z /= w;
//    }

    return res;
}

Vec3d Vec3d::operator+=(const Vec3d &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vec3d Vec3d::operator-=(const Vec3d &other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

float Vec3d::similarity(const Vec3d &other) const
{
    return dot(other) / (diff() * other.diff());
}
