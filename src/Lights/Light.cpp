#include "Light.h"

Light::Light(SDL_Color _color)
        : color(_color),
          rgbStrength(
                  {(float) _color.r / 255.0f, (float) _color.g / 255.0f, (float) _color.b / 255.0f})
{
}

void Light::SetColor(SDL_Color _color)
{
    this->color = _color;
    rgbStrength = {(float) _color.r / 255.0f, (float) _color.g / 255.0f, (float) _color.b / 255.0f};
}
