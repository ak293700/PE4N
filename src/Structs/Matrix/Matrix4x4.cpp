#include <cmath>
#include "Matrix4x4.h"
#include <iostream>
#include "../Camera/Camera.h"

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
    res.set(0, 0, get(0, 0) * other.get(0, 0) + get(1, 0) * other.get(0, 1) + get(2, 0) * other.get(0, 2) +
                  get(3, 0) * other.get(0, 3));
    res.set(1, 0, get(0, 0) * other.get(1, 0) + get(1, 0) * other.get(1, 1) + get(2, 0) * other.get(1, 2) +
                  get(3, 0) * other.get(1, 3));
    res.set(2, 0, get(0, 0) * other.get(2, 0) + get(1, 0) * other.get(2, 1) + get(2, 0) * other.get(2, 2) +
                  get(3, 0) * other.get(2, 3));
    res.set(3, 0, get(0, 0) * other.get(3, 0) + get(1, 0) * other.get(3, 1) + get(2, 0) * other.get(3, 2) +
                  get(3, 0) * other.get(3, 3));
    res.set(0, 1, get(0, 1) * other.get(0, 0) + get(1, 1) * other.get(0, 1) + get(2, 1) * other.get(0, 2) +
                  get(3, 1) * other.get(0, 3));
    res.set(1, 1, get(0, 1) * other.get(1, 0) + get(1, 1) * other.get(1, 1) + get(2, 1) * other.get(1, 2) +
                  get(3, 1) * other.get(1, 3));
    res.set(2, 1, get(0, 1) * other.get(2, 0) + get(1, 1) * other.get(2, 1) + get(2, 1) * other.get(2, 2) +
                  get(3, 1) * other.get(2, 3));
    res.set(3, 1, get(0, 1) * other.get(3, 0) + get(1, 1) * other.get(3, 1) + get(2, 1) * other.get(3, 2) +
                  get(3, 1) * other.get(3, 3));
    res.set(0, 2, get(0, 2) * other.get(0, 0) + get(1, 2) * other.get(0, 1) + get(2, 2) * other.get(0, 2) +
                  get(3, 2) * other.get(0, 3));
    res.set(1, 2, get(0, 2) * other.get(1, 0) + get(1, 2) * other.get(1, 1) + get(2, 2) * other.get(1, 2) +
                  get(3, 2) * other.get(1, 3));
    res.set(2, 2, get(0, 2) * other.get(2, 0) + get(1, 2) * other.get(2, 1) + get(2, 2) * other.get(2, 2) +
                  get(3, 2) * other.get(2, 3));
    res.set(3, 2, get(0, 2) * other.get(3, 0) + get(1, 2) * other.get(3, 1) + get(2, 2) * other.get(3, 2) +
                  get(3, 2) * other.get(3, 3));
    res.set(0, 3, get(0, 3) * other.get(0, 0) + get(1, 3) * other.get(0, 1) + get(2, 3) * other.get(0, 2) +
                  get(3, 3) * other.get(0, 3));
    res.set(1, 3, get(0, 3) * other.get(1, 0) + get(1, 3) * other.get(1, 1) + get(2, 3) * other.get(1, 2) +
                  get(3, 3) * other.get(1, 3));
    res.set(2, 3, get(0, 3) * other.get(2, 0) + get(1, 3) * other.get(2, 1) + get(2, 3) * other.get(2, 2) +
                  get(3, 3) * other.get(2, 3));
    res.set(3, 3, get(0, 3) * other.get(3, 0) + get(1, 3) * other.get(3, 1) + get(2, 3) * other.get(3, 2) +
                  get(3, 3) * other.get(3, 3));

    return res;
}

Vec3 Matrix4x4::operator*(const Vec3 &other) const
{
    return {
            other.x * get(0, 0) + other.y * get(0, 1) + other.z * get(0, 2) + get(0, 3),
            other.x * get(1, 0) + other.y * get(1, 1) + other.z * get(1, 2) + get(1, 3),
            other.x * get(2, 0) + other.y * get(2, 1) + other.z * get(2, 2) + get(2, 3),
    };
}

inline Matrix4x4 Matrix4x4::Identity()
{
    return {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
}

Matrix4x4 Matrix4x4::Translation(const Vec3 &translation)
{
    return {
            1, 0, 0, translation.x,
            0, 1, 0, translation.y,
            0, 0, 1, translation.z,
            0, 0, 0, 1
    };
}

Matrix4x4 Matrix4x4::RotationX(float angle)
{
    float cos = cosf(angle);
    float sin = sinf(angle);

    return {
            1, 0, 0, 0,
            0, cos, -sin, 0,
            0, sin, cos, 0,
            0, 0, 0, 1
    };
}

Matrix4x4 Matrix4x4::RotationY(float angle)
{
    float cos = cosf(angle);
    float sin = sinf(angle);

    return {
            cos, 0, sin, 0,
            0, 1, 0, 0,
            -sin, 0, cos, 0,
            0, 0, 0, 1
    };
}

Matrix4x4 Matrix4x4::RotationZ(float angle)
{
    float cos = cosf(angle);
    float sin = sinf(angle);

    return {
            cos, -sin, 0, 0,
            sin, cos, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
}

Matrix4x4 Matrix4x4::PointAt(const Vec3 &pos, const Vec3 &forward, const Vec3 &up, const Vec3 &right)
{
    return {
            right.x, right.y, right.z, 0.0f,
            up.x, up.y, up.z, 0.0f,
            forward.x, forward.y, forward.z, 0.0f,
            pos.x, pos.y, pos.z, 1.0f
    };
}

Matrix4x4 Matrix4x4::QuickInverse(const Matrix4x4 &m)
{
    Vec3 AxisX = {m.get(0, 0), m.get(1, 0), m.get(2, 0)};
    Vec3 AxisY = {m.get(0, 1), m.get(1, 1), m.get(2, 1)};
    Vec3 AxisZ = {m.get(0, 2), m.get(1, 2), m.get(2, 2)};
    Vec3 Translation = {m.get(0, 3), m.get(1, 3), m.get(2, 3)};

    return {
            AxisX.x, AxisY.x, AxisZ.x, 0.0f,
            AxisX.y, AxisY.y, AxisZ.y, 0.0f,
            AxisX.z, AxisY.z, AxisZ.z, 0.0f,
            -Translation.dot(AxisX), -Translation.dot(AxisY), -Translation.dot(AxisZ), 1.0f
    };

    /*return {
        m.get(0, 0), m.get(1, 0), m.get(2, 0), 0,
        m.get(0, 1), m.get(1, 1), m.get(2, 1), 0,
        m.get(0, 2), m.get(1, 2), m.get(2, 2), 0,
        -(m.get(3, 0) * m.get(0, 0) + m.get(3, 1) * m.get(1, 0) + m.get(3, 2) * m.get(2, 0)),
        -(m.get(3, 0) * m.get(0, 1) + m.get(3, 1) * m.get(1, 1) + m.get(3, 2) * m.get(2, 1)),
        -(m.get(3, 0) * m.get(0, 2) + m.get(3, 1) * m.get(1, 2) + m.get(3, 2) * m.get(2, 2)),
        1.0f
    };*/
}

void Matrix4x4::Print() const
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
            std::cout << get(x, y) << " | ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
