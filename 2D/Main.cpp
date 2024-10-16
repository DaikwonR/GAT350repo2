#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Source\Renderer.h"
#include "Source\Framebuffer.h"
#include "Source\MathUtils.h"
#include "Source\Image.h"
#include "Source\PostProcess.h"
#include "Source\Color.h"
#include "Source\Model.h"

int main(int argc, char* argv[])
{

#pragma region Class Declarations
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);

    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(renderer, 800, 600);
    Image image;
    image.Load("scenic.jpg");

    Image ImageAlpha;
    ImageAlpha.Load("colors.png");
    PostProcess::Alpha(ImageAlpha.m_buffer, 128);




    vertices_t vertices{ glm::vec3{ -5, 5, 0}, glm::vec3{5, 5, 0}, glm::vec3{-5, -5, 0} };
    Model model(vertices, { 255, 0, 0, 255 });

#pragma endregion

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

#pragma region Draw(With Loop)
        int x1 = 400 - rand() % framebuffer.m_width;
        int y1 = 300 - rand() % framebuffer.m_height;
        int x2 = rand() % framebuffer.m_width;
        int y2 = rand() % framebuffer.m_height;
        int x3 = rand() % framebuffer.m_width;
        int y3 = rand() % framebuffer.m_height;

        //for (int i = 0; i < 0; i++)
        //{

            //framebuffer.DrawPoint(10, 10, { 255, 255, 255, 255 });
            //framebuffer.DrawRect(10, 10, 100, 100, {255, 255, 255, 255});
            //framebuffer.DrawLine(x1, y1, x2, y2, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
            //framebuffer.DrawTriangle(x1, y1, x2, y2, x3, y3, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
            //framebuffer.DrawCircle(x1, x2, 15, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
        //}

#pragma endregion

#pragma region Draw(NoLoop)
        framebuffer.DrawImage(100, 100, image);

        //framebuffer.DrawLine(150, 150, 250, 250, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
        //framebuffer.DrawTriangle(120, 225, 225, 125, 125, 120, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
        //framebuffer.DrawCircle(100, 100, 50, { (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255), (uint8_t)(rand() % 255) });
        //framebuffer.DrawRect(10, 10, 100, 100, { 255, 0, 0 });


       /*PostProcess::Invert(framebuffer.m_buffer);

       PostProcess::Brightness(framebuffer.m_buffer, 42);*/

       //PostProcess::Monochrome(framebuffer.m_buffer);

       //PostProcess::Noise(framebuffer.m_buffer, 200);

       //PostProcess::Threshold(framebuffer.m_buffer, 175);

       //PostProcess::Posterization(framebuffer.m_buffer, 255);

        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::BoxBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::GaussianBlur(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);
        //PostProcess::Sharpen(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

        //PostProcess::Emboss(framebuffer.m_buffer, framebuffer.m_width, framebuffer.m_height);

#pragma endregion

#pragma region MouseTracking
        int mx, my;
        SDL_GetMouseState(&mx, &my);

        //framebuffer.DrawLinearCurve(100, 100, 200, 200, { 255, 255, 255, 255 });
        ////framebuffer.DrawQuadraticCurve(100, 200, mx, my, 300, 200, { 255, 0, 255, 255 });
        //framebuffer.DrawCubicSpline(100, 200, 100, 100, 200, 100, 200, 200, { 255, 0, 0, 255 });

        int ticks = SDL_GetTicks();
        float time = ticks * 0.001f;
        float t = std::abs(std::sin(time));

        //int x, y;
        //CubicPoint(300, 400, 300, 100, mx, my, 600, 400, t, x, y);
        //framebuffer.DrawRect(x - 20, y - 20, 100, 100, { 255, 0, 0, 255 });

#pragma region SetBlendModes

        SetBlendMode(BlendMode::Normal);
        framebuffer.DrawImage(100, 100, image);
        SetBlendMode(BlendMode::Normal);
        framebuffer.DrawImage(mx, my, ImageAlpha);

#pragma endregion



        /*PostProcess::Invert(framebuffer.m_buffer);
        PostProcess::Brightness(framebuffer.m_buffer, 42);
        PostProcess::Monochrome(framebuffer.m_buffer);*/

#pragma endregion

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate(modelMatrix, glm::vec3(240.0f, 240.0f, 0.0f));
        glm::mat4 scale = glm::scale(modelMatrix, glm::vec3(2));
        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), glm::radians(time * 90), glm::vec3{0, 0, 1});

        modelMatrix = translate * scale;

        model.Draw(framebuffer, modelMatrix);

        framebuffer.Update();

        // show screen
        renderer = framebuffer;
        SDL_RenderPresent(renderer.m_renderer);


    }

    return 0;
}