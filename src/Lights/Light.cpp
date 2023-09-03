#include "Light.h"

Light::Light(SDL_Color _color)
        : color(_color),
          rgbStrength(
                  {(float) _color.r / 255.0f, (float) _color.g / 255.0f, (float) _color.b / 255.0f}) {
}

void Light::SetColor(SDL_Color _color) {
    this->color = _color;
    rgbStrength = {(float) _color.r / 255.0f, (float) _color.g / 255.0f, (float) _color.b / 255.0f};
}

SDL_Color Light::addColors(SDL_Color color1, SDL_Color color2) {
    int red = color1.r + color2.r;
    int green = color1.g + color2.g;
    int blue = color1.b + color2.b;

    return {(Uint8) (red < 255 ? red : 255),
            (Uint8) (green < 255 ? green : 255),
            (Uint8) (blue < 255 ? blue : 255),
            255};
}

//SDL_Color Light::subtractColor(SDL_Color color1, SDL_Color color2) {
//    return SDL_Color(
//            color1.r * color2.r,
//            color1.g * color2.g,
//            color1.b * color2.b,
//            1.0f);
//}
