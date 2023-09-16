#pragma once

#include <SDL.h>
#include "../Structs/Triangle/Triangle.h"

class Light
{
public:
    explicit Light(SDL_Color color);
    [[nodiscard]] virtual SDL_Color GetColor(const Triangle &tgl) const = 0;

    void SetColor(SDL_Color color);

    static SDL_Color addColors(SDL_Color color1, SDL_Color color2);
//    static SDL_Color subtractColor(SDL_Color color1, SDL_Color color2);


protected:
    SDL_Color color;
    Vec3d rgbStrength;
};