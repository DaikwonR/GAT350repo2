#include <SDL.h>
#include <iostream>

#include "Source\Renderer.h"
#include "Source\Framebuffer.h"

int main(int argc, char* argv[])
{

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);

    Framebuffer framebuffer(renderer, 400, 300);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
        }
    }

    //// clear screen
    //SDL_SetRenderDrawColor(renderer.m_renderer, 0, 0, 0, 0);
    //SDL_RenderClear(renderer.m_renderer);

    framebuffer.Clear(color_t{ 255, 0, 0, 255 });

    for (int i = 0; i < 100; i++)
    {
        int x = rand() % 256;
        int y = rand() % 101;
        framebuffer.DrawPoint(10, 10, { 255, 255, 255, 255 });
    }

    framebuffer.DrawRect(10, 10, 100, 100,{255, 0, 0});

    framebuffer.Update();

    renderer = framebuffer;
    // renderer.CopyFramebuffer(framebuffer);

    return 0;
}