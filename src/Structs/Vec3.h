#pragma once

struct Vec3
{
    float x;
    float y;
    float z;

    Vec3 CrossProduct(const Vec3 &other) const;

    float DotProduct(const Vec3 &other) const;

    // other - this
    Vec3 Diff(const Vec3& other) const;

    void Print() const;

    float Length() const;

    void Normalize();
};