#pragma once

#include <SDL.h>
#include "../Structs/Vec3/Vec3d.h"
#include "../Structs/Triangle/Triangle.h"
#include "Light.h"

class DirectionalLight : public Light
{
private:
    Vec3d dir{}; // the length must be 1
public:
    DirectionalLight(Vec3d dir, SDL_Color color);
    [[nodiscard]] SDL_Color GetColor(const Triangle& tgl) const override;
    void SetDir(const Vec3d& _dir);
};
