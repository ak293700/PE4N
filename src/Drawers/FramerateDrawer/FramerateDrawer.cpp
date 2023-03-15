#include "FramerateDrawer.h"
#include "../../MainManager/MainManager.h"
#include "../Colors.h"

void displayFPS(int refresh_time)
{
    static Uint64 last_time = 0, current_time;
    static int frames_counted = 0;
    const int string_size = 10;
    static char fps_string[string_size];
    static float fps = 0;

    current_time = SDL_GetTicks64();

    if (last_time == 0)
        last_time = current_time++;

    bool recompute = current_time > last_time + refresh_time;
    if (!recompute)
        frames_counted++;
    else
        fps = (float) frames_counted / ((float) (current_time - last_time) / 1000.0f);

    int fps_length = snprintf(fps_string, 10, "%.2f", fps);

    // Handle error condition where the formatted string is too long for the buffer
    if (fps_length < 0 || fps_length >= 10)
        fps_string[string_size - 1] = 0; // we add the end of string 0 and continue the function

    SDL_Surface *fps_surface = TTF_RenderText_Solid(MainManager::font,fps_string,Colors::White);

    SDL_Texture *fps_texture = SDL_CreateTextureFromSurface(MainManager::renderer, fps_surface);
    SDL_Rect fps_rect = {5, 5, fps_surface->w, fps_surface->h};

    SDL_RenderCopy(MainManager::renderer, fps_texture, nullptr, &fps_rect);

    SDL_DestroyTexture(fps_texture);
    SDL_FreeSurface(fps_surface);

    if (recompute)
    {
        last_time = current_time;
        frames_counted = 0;
    }
}
