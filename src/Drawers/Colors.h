#include <SDL.h>

class Colors {
private:
    Colors()
    {}
public:
    constexpr static const SDL_Color White = {255, 255, 255, 255};
    constexpr static const SDL_Color Black = {0, 0, 0, 255};
    constexpr static const SDL_Color Red = {255, 0, 0, 255};
    constexpr static const SDL_Color Green = {0, 255, 0, 255};
    constexpr static const SDL_Color Blue = {0, 0, 255, 255};
};