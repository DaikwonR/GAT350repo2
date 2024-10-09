#include <SDL.h>
#include <iostream>

#include "Source\Renderer.h"
#include "Source\Framebuffer.h"
#include "Source\MathUtils.h"
#include "Source\Image.h"
#include "Source\PostProcess.h"

int main(int argc, char* argv[])
{

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);

    Framebuffer framebuffer(renderer, 400, 300);
    Image image;
    image.Load("scenic.jpg");

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

        framebuffer.Clear(color_t{ 0, 0, 0, 255 });

        int x1 = 400 - rand() % framebuffer.m_width;
        int y1 = 300 - rand() % framebuffer.m_height;
        int x2 = rand() % framebuffer.m_width;
        int y2 = rand() % framebuffer.m_height;
        int x3 = rand() % framebuffer.m_width;
        int y3 = rand() % framebuffer.m_height;

        for (int i = 0; i < 0; i++)
        {

            //framebuffer.DrawPoint(10, 10, { 255, 255, 255, 255 });
            //framebuffer.DrawRect(10, 10, 100, 100, {255, 255, 255, 255});
            //framebuffer.DrawLine(x1, y1, x2, y2, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
            //framebuffer.DrawTriangle(x1, y1, x2, y2, x3, y3, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
            //framebuffer.DrawCircle(x1, x2, 15, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
        }

        framebuffer.DrawImage(100, 100, image);

        //framebuffer.DrawLine(150, 150, 250, 250, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
        //framebuffer.DrawTriangle(120, 225, 225, 125, 125, 120, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
        //framebuffer.DrawCircle(100, 100, 50, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
        //framebuffer.DrawRect(10, 10, 100, 100, { 255, 0, 0 });

        int mx, my;
        SDL_GetMouseState(&mx, &my);

        framebuffer.DrawLinearCurve(100, 100, 200, 200, { 255, 255, 255, 255 });
        //framebuffer.DrawQuadraticCurve(100, 200, mx, my, 300, 200, { 255, 0, 255, 255 });
        framebuffer.DrawCubicSpline(100, 200, 100, 100, 200, 100, 200, 200, { 255, 0, 0, 255 });

        int ticks = SDL_GetTicks();
        float time = ticks * 0.01f;
        float t = std::abs(std::sin(time));
        int x, y;
        CubicPoint(300, 400, 300, 100, mx, my, 600, 400, t, x, y);
        //framebuffer.DrawRect(x - 20, y - 20, 100, 100, { 255, 0, 0, 255 });

        PostProcess::Invert(framebuffer.m_buffer);
        PostProcess::Brightness(framebuffer.m_buffer, 42);
        PostProcess::Monochrome(framebuffer.m_buffer);

        framebuffer.Update();

        // show screen
        renderer = framebuffer;
        SDL_RenderPresent(renderer.m_renderer);


    }


    return 0;
}