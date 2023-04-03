#pragma once

#include "Vec3.h"

struct Triangle
{
    Vec3 a;
    Vec3 b;
    Vec3 c;

    [[nodiscard]] Vec3 norm() const;

    void print() const;
};