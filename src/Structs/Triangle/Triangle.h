#pragma once

#include "../Vec3/Vec3.h"
#include "../Texture/Texture.h"

struct Triangle
{
    Vec3 a;
    Vec3 b;
    Vec3 c;
    Texture texture;

    [[nodiscard]] Vec3 norm() const;

    void print() const;
};