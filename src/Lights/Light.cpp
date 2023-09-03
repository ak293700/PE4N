#include <iostream>
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
    float alfa1 = (float)color1.a / 255.0f;
    float alfa2 = (float)color2.a / 255.0f;

//    std::cout << (int)color1.a << ' ' << (int)color2.a << std::endl;
//    std::cout << alfa1 << ' ' << alfa2 << std::endl;

    float red = (float)color1.r * alfa1 + (float)color2.r * alfa2;
    float green = (float)color1.g * alfa1 + (float)color2.g * alfa2;
    float blue = (float)color1.b * alfa1 + (float)color2.b * alfa2;



    return {(Uint8) (red < 255.0f ? red : 255.0f),
            (Uint8) (green < 255.0f ? green : 255.0f),
            (Uint8) (blue < 255.0f ? blue : 255.0f),
            255};
}

//SDL_Color Light::subtractColor(SDL_Color color1, SDL_Color color2) {
//    return SDL_Color(
//            color1.r * color2.r,
//            color1.g * color2.g,
//            color1.b * color2.b,
//            1.0f);
//}
