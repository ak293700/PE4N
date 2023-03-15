#include "MainManager.h"
#include "../Drawers/FramerateDrawer/FramerateDrawer.h"
#include "../Drawers/Colors.h"

SDL_Window *MainManager::window = nullptr;
SDL_Renderer *MainManager::renderer = nullptr;
std::string MainManager::font_path = "/Library/Fonts/Arial Unicode.ttf";
TTF_Font *MainManager::font = nullptr;
float MainManager::aspectRatio = 0.0f;
int MainManager::width = 0;
int MainManager::height = 0;
Scene MainManager::scene = *new Scene();

void MainManager::Init(int _width, int _height)
{
    width = _width;
    height = _height;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(SDL_GetError());

    if (TTF_Init() != 0)
        throw std::runtime_error(TTF_GetError());

    font = TTF_OpenFont(font_path.c_str(), 14);
    if (font == nullptr)
        throw std::runtime_error(TTF_GetError());

    window = SDL_CreateWindow("My Game",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);

    aspectRatio = (float) height / (float) width;

    scene.Init();
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void MainManager::Quit()
{
    scene.Quit();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}

inline void MainManager::Clear()
{
//     Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void MainManager::Main()
{
    Uint64 last_frame_time = SDL_GetTicks64();
    Uint64 current_time;
    while (true)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    return;
            }
        }


        current_time = SDL_GetTicks();
        Run(((float) (current_time - last_frame_time)) / 1000.0f);
        last_frame_time = current_time;
    }
}


void MainManager::Run(float delta)
{
    Clear();
    scene.Render(delta);
    displayFPS();

    SDL_RenderPresent(MainManager::renderer);
}
