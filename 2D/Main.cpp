#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "Source\Renderer.h"
#include "Source\Framebuffer.h"
#include "Source\MathUtils.h"
#include "Source\Image.h"
#include "Source\PostProcess.h"
#include "Source\Color.h"
#include "Source\Model.h"
#include "Source\Transform.h"
#include "Source\ETime.h"
#include "Source\Input.h"
#include "Source\Camera.h"
#include "Source\Actor.h"
#include "Source\Random.h"

int main(int argc, char* argv[])
{

#pragma region Class Declarations

    Time time;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("2D", 800, 600);

    Input input;
    input.Initialize();
    input.Update();


    SetBlendMode(BlendMode::Normal);

    Camera camera(renderer.m_width, renderer.m_height);
    camera.SetView(glm::vec3{ 0, 0, -20 }, glm::vec3{ 0 });
    camera.SetProjection(60.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform cameraTransform{ { 0, 0, -20 } };

    Framebuffer framebuffer(renderer, 800, 600);
    Image image;
    //image.Load("scenic.jpg");

    Image ImageAlpha;
    //ImageAlpha.Load("colors.png");
    PostProcess::Alpha(ImageAlpha.m_buffer, 120);

    vertices_t vertices{ glm::vec3{ -5, 5, 0}, glm::vec3{5, 5, 0}, glm::vec3{-5, -5, 0} };
    //Model model(vertices, { 255, 0, 0, 255 });

    std::shared_ptr<Model> model = std::make_shared<Model>();
    model->Load("busgame.obj");
    model->SetColor({ 255, 0, 0, 255 });

    std::vector<std::unique_ptr<Actor>> actors;
    for (int i = 0; i < 20; i++)
    {
        Transform transform{ { randomf(-10.0f, 10.0f), randomf(-10.0f, 10.0f), randomf(-10.0f, 10.0f) }, glm::vec3{0, 0, 0}, glm::vec3{ randomf(2, 20) } };
        std::unique_ptr<Actor> actor = std::make_unique<Actor>(transform, model);
        actor->SetColor({ (uint8_t)random(256), (uint8_t)random(256), (uint8_t)random(256), 255 });
        actors.push_back(std::move(actor));
    }



#pragma endregion
    time.Tick();
    input.Update();

    bool quit = false;
    while (!quit)
    {
        time.Tick();

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
        //framebuffer.DrawImage(100, 100, image);

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

        /*PostProcess::Invert(framebuffer.m_buffer);
        PostProcess::Brightness(framebuffer.m_buffer, 42);
        PostProcess::Monochrome(framebuffer.m_buffer);*/

#pragma endregion

#pragma region MouseTracking
        int mx, my;
        SDL_GetMouseState(&mx, &my);

        //framebuffer.DrawLinearCurve(100, 100, 200, 200, { 255, 255, 255, 255 });
        ////framebuffer.DrawQuadraticCurve(100, 200, mx, my, 300, 200, { 255, 0, 255, 255 });
        //framebuffer.DrawCubicSpline(100, 200, 100, 100, 200, 100, 200, 200, { 255, 0, 0, 255 });

        //int x, y;
        //CubicPoint(300, 400, 300, 100, mx, my, 600, 400, t, x, y);
        //framebuffer.DrawRect(x - 20, y - 20, 100, 100, { 255, 0, 0, 255 });

#pragma region SetBlendModes

        SetBlendMode(BlendMode::Normal);
        framebuffer.DrawImage(100, 100, image);
        SetBlendMode(BlendMode::Normal);
        framebuffer.DrawImage(mx, my, ImageAlpha);

#pragma endregion

#pragma endregion

#pragma region CameraMovement
        if (input.GetMouseButtonDown(2))
        {
            input.SetRelativeMode(true);

            glm::vec3 direction{ 0 };
            if (input.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
            if (input.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
            if (input.GetKeyDown(SDL_SCANCODE_E)) direction.y = 1;
            if (input.GetKeyDown(SDL_SCANCODE_Q)) direction.y = -1;
            if (input.GetKeyDown(SDL_SCANCODE_W)) direction.z = 1;
            if (input.GetKeyDown(SDL_SCANCODE_S)) direction.z = -1;

            cameraTransform.rotation.y += input.GetMouseRelative().x * 0.25f;
            cameraTransform.rotation.x += input.GetMouseRelative().y * 0.25f;

            glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction, 0 };

            cameraTransform.position += offset * 70.0f * time.GetDeltaTime();

        }
        else
        {
            input.SetRelativeMode(false);
        }

        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());

        for (auto& actor : actors)
        {
            actor->Draw(framebuffer, camera);
        }
#pragma endregion



        framebuffer.Update();

        // show screen
        renderer = framebuffer;
        SDL_RenderPresent(renderer.m_renderer);


    }

    return 0;
}