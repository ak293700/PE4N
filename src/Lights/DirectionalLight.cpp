#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vec3 dir, SDL_Color color)
        : Light(color), dir(dir)
{
}

SDL_Color DirectionalLight::GetColor(const Triangle &tgl) const
{
    Vec3 norm = tgl.norm();
    float dP = norm.DotProduct(dir);
    float nL = norm.Length();

    float same = 0.0f;
    if (nL != 0.0f)
        same = dP / nL;

    float grayscale = 255.0f * same * 0.5f + 255.0f;
    return {(Uint8) (grayscale * rgbStrength.x),
            (Uint8) (grayscale * rgbStrength.y),
            (Uint8) (grayscale * rgbStrength.z),
            255};
}
