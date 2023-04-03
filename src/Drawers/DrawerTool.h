#pragma once

#include <SDL.h>
#include "../Structs/Vec2/Vec2.h"
#include "../Structs/Triangle/Triangle.h"

void Draw2dTriangle(const Vec2& a, const Vec2& b, const Vec2& c, const SDL_Color& color);

void Draw2dTriangleOutline(const Vec2& a, const Vec2& b, const Vec2& c, const SDL_Color& color);

void Draw2dTriangle(const Vec2& a, const Vec2& b, const Vec2& c);

void DrawLine(const Vec2& a, const Vec2& b, SDL_Color color);

void DrawLineImpl(const Vec2& a, const Vec2& b);

void SetColor(const SDL_Color& color);

void DrawFilledCircle(const Vec2& center, float radius, const SDL_Color& color);


