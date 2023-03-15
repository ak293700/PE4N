#include "Light.h"

Light::Light(SDL_Color color) : color(color), rgbStrength({color.r / 255.0f, color.g / 255.0f, color.b / 255.0f})
{

}

void Light::SetColor(SDL_Color color)
{
    this->color = color;
    rgbStrength = {color.r / 255.0f, color.g / 255.0f, color.b / 255.0f};
}
