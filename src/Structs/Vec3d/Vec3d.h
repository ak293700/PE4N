#pragma once

#include "../Matrix/Matrix4x4.h"

struct Matrix4x4;

struct Vec3d {
    float x;
    float y;
    float z;
    float w;

    [[nodiscard]] Vec3d cross(const Vec3d &other) const;

    [[nodiscard]] float dot(const Vec3d &other) const;

    // other - this
    [[nodiscard]] Vec3d diff(const Vec3d &other) const;

    void print() const;

    [[nodiscard]] float diff() const;

    [[nodiscard]] Vec3d normalize() const;

    [[nodiscard]] Vec3d operator+(const Vec3d &other) const;

    [[nodiscard]] Vec3d operator-(const Vec3d &other) const;

    [[nodiscard]] Vec3d operator+(float other) const;

    [[nodiscard]] Vec3d operator-(float other) const;

    [[nodiscard]] Vec3d operator*(float other) const;

    [[nodiscard]] Vec3d operator/(float other) const;

    [[nodiscard]] Vec3d operator*(const Matrix4x4 &m) const;

    Vec3d operator+=(const Vec3d &other);

    Vec3d operator-=(const Vec3d &other);

    inline static Vec3d Zero() {
        return {0, 0, 0};
    };

    inline static Vec3d One() {
        return {1, 1, 1};
    };

    [[nodiscard]] float similarity(const Vec3d &other) const;
};