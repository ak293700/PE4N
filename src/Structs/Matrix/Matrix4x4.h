#pragma once

#include "../Vec3d/Vec3d.h"
struct Vec3d;

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

    [[nodiscard]] Vec3d operator*(const Vec3d &other) const;

    inline static Matrix4x4 Zero()
    {
        return {};
    };

    static Matrix4x4 Identity();

    static Matrix4x4 Translation(const Vec3d &translation);

    static Matrix4x4 RotationX(float angle);

    static Matrix4x4 RotationY(float angle);

    static Matrix4x4 RotationZ(float angle);

    static Matrix4x4 PointAt(const Vec3d &pos, const Vec3d &forward, const Vec3d &up, const Vec3d &right);

    static Matrix4x4 QuickInverse(const Matrix4x4 &m); // Only for Rotation/Translation Matrices

    void Print() const;
};