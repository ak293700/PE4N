#pragma once

#include <SDL.h>
#include "../Structs/Vec3.h"
#include "../Structs/Triangle.h"

class DirectionalLight
{
public:
    DirectionalLight(Vec3 dir);
    Vec3 dir{}; // the length must be 1
    SDL_Color GetColor(const Triangle& tgl) const;
};
