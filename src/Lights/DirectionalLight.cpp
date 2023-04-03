#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Vec3 dir, SDL_Color color)
        : Light(color), dir(dir.normalize())
{
}

SDL_Color DirectionalLight::GetColor(const Triangle &tgl) const
{
    Vec3 norm = tgl.norm() * -1.0f;
    float dP = norm.dot(dir);
    float nL = norm.diff();

    float same = 1.0f;
    if (nL != 0.0f)
        same = dP / nL;

    // clamp same to -1.0f and 1.0f
    if (same < -1.0f)
        same = -1.0f;
    else if (same > 1.0f)
        same = 1.0f;

    const float mid = 255.0f * 0.5f;
    float grayscale = mid * same + mid;
    return {(Uint8) (grayscale * rgbStrength.x),
            (Uint8) (grayscale * rgbStrength.y),
            (Uint8) (grayscale * rgbStrength.z),
            255};
}

void DirectionalLight::SetDir(const Vec3 &_dir)
{
    dir = _dir.normalize();
}
