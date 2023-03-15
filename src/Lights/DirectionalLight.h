#pragma once

#include <SDL.h>
#include "../Structs/Vec3.h"
#include "../Structs/Triangle.h"
#include "Light.h"

class DirectionalLight : public Light
{
public:
    Vec3 dir{}; // the length must be 1

    DirectionalLight(Vec3 dir, SDL_Color color);
    [[nodiscard]] SDL_Color GetColor(const Triangle& tgl) const override;
};
