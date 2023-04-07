#include "Application.h"
#include "../Drawers/FramerateDrawer/UiDrawer.h"
#include "../Drawers/Colors.h"
#include "../Structs/Vec2/Vec2.h"


SDL_Window *Application::window;
SDL_Renderer *Application::renderer;
std::string Application::font_path;
TTF_Font *Application::font;
float Application::aspectRatio;
int Application::width;
int Application::height;
Scene *Application::scene;

void Application::Init(int _width, int _height)
{
    width = _width;
    height = _height;
    aspectRatio = (float) height / (float) width;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        throw std::runtime_error(SDL_GetError());

    if (TTF_Init() != 0)
        throw std::runtime_error(TTF_GetError());

    font_path = "/Library/Fonts/Arial Unicode.ttf";
    font = TTF_OpenFont(font_path.c_str(), 14);
    if (font == nullptr)
        throw std::runtime_error(TTF_GetError());

    window = SDL_CreateWindow("PE4N",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              width, height,
                              SDL_WINDOW_SHOWN);

//    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    // TODO: Create a thread for the rendering and do the computation in another thread

}

void Application::Quit()
{
    scene->Quit();
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    TTF_Quit();
    SDL_Quit();
}

inline void Application::Clear()
{
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Application::Main()
{
    Uint64 last_frame_time = SDL_GetTicks64();
    Uint64 current_time;
    while (true)
    {
        current_time = SDL_GetTicks();
        float delta = ((float) (current_time - last_frame_time)) / 1000.0f;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    return;
            }
        }

        last_frame_time = current_time;
        Run(delta);
    }
}

void Application::Run(float delta)
{
    Clear();
    int x, y;
    SDL_GetMouseState(&x, &y);

    scene->MoveCamera(delta);
    scene->camera.RecomputeForwardUpAndRight();
    scene->Render(delta);
    displayFPS();
    displayOrientation(scene->camera.yaw);

    SDL_RenderPresent(Application::renderer);
}

