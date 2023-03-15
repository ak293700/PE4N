#include "DrawerTool.h"
#include "../MainManager/MainManager.h"
#include "Colors.h"

void Draw2dTriangle(const Vec2 &a, const Vec2 &b, const Vec2 &c, const SDL_Color &color)
{
    SetColor(color);

    // Sort the vertices by their y-coordinates
    Vec2 bottom = a;
    Vec2 middle = b;
    Vec2 top = c;

    if (bottom.y > middle.y)
        std::swap(bottom, middle);
    if (bottom.y > top.y)
        std::swap(bottom, top);
    if (middle.y > top.y)
        std::swap(middle, top);

    // Calculate the slopes of the three edges of the triangle
    float slope1 = (top.x - bottom.x) / (top.y - bottom.y);
    float slope2 = (middle.x - bottom.x) / (middle.y - bottom.y);
    float slope3 = (top.x - middle.x) / (top.y - middle.y);

    // Determine the y-coordinate range for the bottom and middle edges of the triangle
    int bottomYInt = (int)std::ceil(bottom.y);
    int middleYInt = (int)std::floor(middle.y);

    // Draw the bottom and middle edges of the triangle
    for (int i = bottomYInt; i <= middleYInt; i++)
    {
        float x1 = bottom.x + ((float)i - bottom.y) * slope1;
        float x2 = bottom.x + ((float)i - bottom.y) * slope2;
        SDL_RenderDrawLine(MainManager::renderer, (int)std::ceil(x1), i, (int)std::floor(x2), i);
    }

    // Determine the y-coordinate range for the top edge of the triangle
    int topYInt = (int)std::floor(top.y);

    // Draw the top edge of the triangle
    for (int i = middleYInt + 1; i <= topYInt; i++)
    {
        float x1 = bottom.x + ((float)i - bottom.y) * slope1;
        float x2 = middle.x + ((float)i - middle.y) * slope3;
        SDL_RenderDrawLine(MainManager::renderer, (int)std::ceil(x1), i, (int)std::floor(x2), i);
    }
}


void Draw2dTriangleOutline(const Vec2 &a, const Vec2 &b, const Vec2 &c, const SDL_Color &color)
{
    SetColor(color);
    SDL_RenderDrawLine(MainManager::renderer, (int) a.x, (int) a.y, (int) b.x, (int) b.y);
    SDL_RenderDrawLine(MainManager::renderer, (int) b.x, (int) b.y, (int) c.x, (int) c.y);
    SDL_RenderDrawLine(MainManager::renderer, (int) c.x, (int) c.y, (int) a.x, (int) a.y);
}

inline void SetColor(const SDL_Color &color)
{
    SDL_SetRenderDrawColor(MainManager::renderer, color.r, color.g, color.b, color.a);
}

void DrawLine(const Vec2 &a, const Vec2 &b, const SDL_Color &color)
{
    SetColor(color);
    DrawLineImpl(a, b);
}

inline void DrawLineImpl(const Vec2 &a, const Vec2 &b)
{
    SDL_RenderDrawLine(MainManager::renderer, (int) a.x, (int) a.y, (int) b.x, (int) b.y);
}
