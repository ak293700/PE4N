#include "DirectionalLight.h"
#include <iostream>

DirectionalLight::DirectionalLight(Vec3 dir) : dir(dir)
{
    dir.Normalize();
}

SDL_Color DirectionalLight::GetColor(const Triangle &tgl) const
{
    Vec3 norm = tgl.norm();
    float dP = norm.DotProduct(dir);
    float nL = norm.Length();

    float same = 0.0f;
    if (nL != 0.0f)
        same = dP / nL;

    Uint8 grayscale = (Uint8)(255.0f * same * 0.5f + 255.0f);
    return {grayscale, grayscale, grayscale, 255};
}
