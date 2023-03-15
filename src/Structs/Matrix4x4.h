#pragma once

#include "Vec3.h"
struct Vec3;

struct Matrix4x4
{
    static const int C = 4;
    static const int L = C * C;

    float m[L];

    inline float get(int x, int y) const
    {
        return m[C * y + x];
    }

    inline void set(int x, int y, float value)
    {
        m[C * y + x] = value;
    }

    [[nodiscard]] Matrix4x4 Transpose() const;

    [[nodiscard]] Matrix4x4 operator*(const Matrix4x4 &other) const;

    [[nodiscard]] Vec3 operator*(const Vec3 &other) const;

    inline static Matrix4x4 Zero()
    {
        return {};
    };
};