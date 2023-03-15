#pragma once

#include <SDL.h>
#include <iostream>
#include <SDL_ttf.h>
#include "../Scene/Scene.h"


class MainManager
{
private:
    // so it cannot be instantiated
    MainManager()
    {}

public:
    static void Init(int width, int height);

    static void Main();

    static void Quit();

    static void Clear();

    static int width;
    static int height;

    static SDL_Window *window;
    static SDL_Renderer *renderer;
    static std::string font_path;
    static TTF_Font *font;
    static Scene scene;
    static float aspectRatio; // aspect ratio of the screen
private:
    static void Run(float delta);
};
