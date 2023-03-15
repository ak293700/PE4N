#include "Matrix4x4.h"

Matrix4x4 Matrix4x4::Transpose() const
{
    return {
            get(0, 0), get(1, 0), get(2, 0), get(3, 0),
            get(0, 1), get(1, 1), get(2, 1), get(3, 1),
            get(0, 2), get(1, 2), get(2, 2), get(3, 2),
            get(0, 3), get(1, 3), get(2, 3), get(3, 3)
    };
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &other) const
{
    // very fast, no loop
    Matrix4x4 res = Matrix4x4::Zero();
    res.set(0, 0, get(0, 0) * other.get(0, 0) + get(1, 0) * other.get(0, 1) + get(2, 0) * other.get(0, 2) + get(3, 0) * other.get(0, 3));
    res.set(1, 0, get(0, 0) * other.get(1, 0) + get(1, 0) * other.get(1, 1) + get(2, 0) * other.get(1, 2) + get(3, 0) * other.get(1, 3));
    res.set(2, 0, get(0, 0) * other.get(2, 0) + get(1, 0) * other.get(2, 1) + get(2, 0) * other.get(2, 2) + get(3, 0) * other.get(2, 3));
    res.set(3, 0, get(0, 0) * other.get(3, 0) + get(1, 0) * other.get(3, 1) + get(2, 0) * other.get(3, 2) + get(3, 0) * other.get(3, 3));
    res.set(0, 1, get(0, 1) * other.get(0, 0) + get(1, 1) * other.get(0, 1) + get(2, 1) * other.get(0, 2) + get(3, 1) * other.get(0, 3));
    res.set(1, 1, get(0, 1) * other.get(1, 0) + get(1, 1) * other.get(1, 1) + get(2, 1) * other.get(1, 2) + get(3, 1) * other.get(1, 3));
    res.set(2, 1, get(0, 1) * other.get(2, 0) + get(1, 1) * other.get(2, 1) + get(2, 1) * other.get(2, 2) + get(3, 1) * other.get(2, 3));
    res.set(3, 1, get(0, 1) * other.get(3, 0) + get(1, 1) * other.get(3, 1) + get(2, 1) * other.get(3, 2) + get(3, 1) * other.get(3, 3));
    res.set(0, 2, get(0, 2) * other.get(0, 0) + get(1, 2) * other.get(0, 1) + get(2, 2) * other.get(0, 2) + get(3, 2) * other.get(0, 3));
    res.set(1, 2, get(0, 2) * other.get(1, 0) + get(1, 2) * other.get(1, 1) + get(2, 2) * other.get(1, 2) + get(3, 2) * other.get(1, 3));
    res.set(2, 2, get(0, 2) * other.get(2, 0) + get(1, 2) * other.get(2, 1) + get(2, 2) * other.get(2, 2) + get(3, 2) * other.get(2, 3));
    res.set(3, 2, get(0, 2) * other.get(3, 0) + get(1, 2) * other.get(3, 1) + get(2, 2) * other.get(3, 2) + get(3, 2) * other.get(3, 3));
    res.set(0, 3, get(0, 3) * other.get(0, 0) + get(1, 3) * other.get(0, 1) + get(2, 3) * other.get(0, 2) + get(3, 3) * other.get(0, 3));
    res.set(1, 3, get(0, 3) * other.get(1, 0) + get(1, 3) * other.get(1, 1) + get(2, 3) * other.get(1, 2) + get(3, 3) * other.get(1, 3));
    res.set(2, 3, get(0, 3) * other.get(2, 0) + get(1, 3) * other.get(2, 1) + get(2, 3) * other.get(2, 2) + get(3, 3) * other.get(2, 3));
    res.set(3, 3, get(0, 3) * other.get(3, 0) + get(1, 3) * other.get(3, 1) + get(2, 3) * other.get(3, 2) + get(3, 3) * other.get(3, 3));

    return res;
}

Vec3 Matrix4x4::operator*(const Vec3 &other) const
{
    return {
            other.x * get(0, 0) + other.y * get(1, 0) + other.z * get(2, 0) + get(3, 0),
            other.x * get(0, 1) + other.y * get(1, 1) + other.z * get(2, 1) + get(3, 1),
            other.x * get(0, 2) + other.y * get(1, 2) + other.z * get(2, 2) + get(3, 2)
    };
}
