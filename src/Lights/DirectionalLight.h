#pragma once

#include <SDL.h>
#include "../Structs/Vec3.h"
#include "../Structs/Triangle.h"
#include "Light.h"

class DirectionalLight : public Light
{
private:
    Vec3 dir{}; // the length must be 1
public:
    DirectionalLight(Vec3 dir, SDL_Color color);
    [[nodiscard]] SDL_Color GetColor(const Triangle& tgl) const override;
    void SetDir(const Vec3& _dir);
};
