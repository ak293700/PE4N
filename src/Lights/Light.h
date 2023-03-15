#pragma once

#include <SDL.h>
#include "../Structs/Triangle.h"

class Light
{
public:
    Light(SDL_Color color);
    virtual SDL_Color GetColor(const Triangle &tgl) const = 0;

    void SetColor(SDL_Color color);

protected:
    SDL_Color color;
    Vec3 rgbStrength;
};