#pragma once

#include "../Vec3d/Vec3d.h"
#include "../Texture/Texture.h"

struct Triangle
{
    Vec3d a;
    Vec3d b;
    Vec3d c;
    Texture texture;

    [[nodiscard]] Vec3d norm() const;

    void print() const;
};