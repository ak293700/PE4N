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
    int bottomYInt = (int) std::ceil(bottom.y);
    int middleYInt = (int) std::floor(middle.y);

    if (!std::isinf(slope2))
    {
        // Draw the bottom and middle edges of the triangle
        for (int i = bottomYInt; i <= middleYInt; i++)
        {
            float x1 = bottom.x + ((float) i - bottom.y) * slope1;
            float x2 = bottom.x + ((float) i - bottom.y) * slope2;

            SDL_RenderDrawLine(MainManager::renderer,
                               (int) std::ceil(x1), MainManager::height - i,
                               (int) std::floor(x2), MainManager::height - i);
        }
    }

    // Determine the y-coordinate range for the top edge of the triangle
    int topYInt = (int) std::floor(top.y);

    if (!std::isinf(slope3))
    {
        // Draw the top edge of the triangle
        for (int i = middleYInt + 1; i <= topYInt; i++)
        {
            float x1 = bottom.x + ((float) i - bottom.y) * slope1;
            float x2 = middle.x + ((float) i - middle.y) * slope3;
            SDL_RenderDrawLine(MainManager::renderer,
                               (int) std::ceil(x1), MainManager::height - i,
                               (int) std::floor(x2), MainManager::height - i);
        }
    }

    Draw2dTriangleOutline(a, b, c, Colors::Red);
}

void Draw2dTriangleOutline(const Vec2 &a, const Vec2 &b, const Vec2 &c, const SDL_Color &color)
{
    SetColor(color);
    int height = MainManager::height;
    SDL_RenderDrawLine(MainManager::renderer, (int) a.x, height - (int) a.y, (int) b.x, height - (int) b.y);
    SDL_RenderDrawLine(MainManager::renderer, (int) b.x, height - (int) b.y, (int) c.x, height - (int) c.y);
    SDL_RenderDrawLine(MainManager::renderer, (int) c.x, height - (int) c.y, (int) a.x, height - (int) a.y);
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

void DrawFilledCircle(const Vec2& center, float radius, const SDL_Color& color)
{
    SetColor(color);
    int x = (int) center.x;
    int y = (int) center.y;
    int r = (int) radius;
    int x0 = x - r;
    int x1 = x + r;
    int y0 = y - r;
    int y1 = y + r;

    for (int i = x0; i <= x1; i++)
    {
        for (int j = y0; j <= y1; j++)
        {
            int dx = i - x;
            int dy = j - y;
            if (dx * dx + dy * dy <= r * r)
                SDL_RenderDrawPoint(MainManager::renderer, i, j);
        }
    }
}