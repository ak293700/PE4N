#pragma once

#include "Matrix4x4.h"
struct Matrix4x4;

struct Vec3
{
    float x;
    float y;
    float z;

    [[nodiscard]] Vec3 cross(const Vec3 &other) const;

    [[nodiscard]] float dot(const Vec3 &other) const;

    // other - this
    [[nodiscard]] Vec3 diff(const Vec3 &other) const;

    void print() const;

    [[nodiscard]] float diff() const;

    [[nodiscard]] Vec3 normalize() const;

    [[nodiscard]] Vec3 operator+(const Vec3 &other) const;

    [[nodiscard]] Vec3 operator-(const Vec3 &other) const;

    [[nodiscard]] Vec3 operator+(float other) const;

    [[nodiscard]] Vec3 operator-(float other) const;

    [[nodiscard]] Vec3 operator*(float other) const;

    [[nodiscard]] Vec3 operator/(float other) const;

    [[nodiscard]] Vec3 operator*(const Matrix4x4 &m) const;

    Vec3 operator+=(const Vec3 &other);
    Vec3 operator-=(const Vec3 &other);

    inline static Vec3 Zero()
    { return {0, 0, 0}; };

    inline static Vec3 One()
    { return {1, 1, 1}; };

    float similarity(const Vec3 &other) const;
};