#pragma once

#include <SDL.h>
#include "../Structs/Triangle.h"

class Light
{
public:
    Light(SDL_Color color);

    SDL_Color color;

    virtual SDL_Color GetColor(const Triangle &tgl) const = 0;

protected:
    Vec3 rgbStrength;
};