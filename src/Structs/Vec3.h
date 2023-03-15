#pragma once

#include "Matrix4x4.h"
struct Matrix4x4;

struct Vec3
{
    float x;
    float y;
    float z;

    [[nodiscard]] Vec3 CrossProduct(const Vec3 &other) const;

    [[nodiscard]] float DotProduct(const Vec3 &other) const;

    // other - this
    [[nodiscard]] Vec3 Diff(const Vec3 &other) const;

    void Print() const;

    [[nodiscard]] float Length() const;

    [[nodiscard]] Vec3 Normalize() const;

    [[nodiscard]] Vec3 operator+(const Vec3 &other) const;

    [[nodiscard]] Vec3 operator-(const Vec3 &other) const;

    [[nodiscard]] Vec3 operator+(float other) const;

    [[nodiscard]] Vec3 operator-(float other) const;

    [[nodiscard]] Vec3 operator*(float other) const;

    [[nodiscard]] Vec3 operator/(float other) const;

    [[nodiscard]] Vec3 operator*(const Matrix4x4 &m) const;

    inline static Vec3 Zero()
    { return {0, 0, 0}; };

    inline static Vec3 One()
    { return {1, 1, 1}; };
};