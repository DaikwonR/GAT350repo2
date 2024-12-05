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
#include "Source\Shader.h"

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
    camera.SetProjection(90.0f, 800.0f / 600, 0.1f, 200.0f);
    Transform cameraTransform{ { 0, 0, -20 } };

    Framebuffer framebuffer(renderer, 800, 600);

    Image image;
    //image.Load("scenic.jpg");

    Image ImageAlpha;
    ImageAlpha.Load("colors.png");
    PostProcess::Alpha(ImageAlpha.m_buffer, 120);

    // shader
    Shader::uniforms.view = camera.GetView();
    Shader::uniforms.projection = camera.GetProjection();
    Shader::uniforms.ambient = color3_t{ 0.01f };

    Shader::uniforms.light.position = glm::vec3{ 10, 10, -10 };
    Shader::uniforms.light.direction = glm::vec3{ 0, -1, 0 };
    Shader::uniforms.light.color = color3_t{ 1 };

    Shader::framebuffer = &framebuffer;

    std::shared_ptr<Model> model = std::make_shared<Model>();
    //model->Load("ww_plane.obj");
    //model->Load("Clouds.obj");
    //model->Load("Bird.obj");
    model->Load("sphere.obj");
    model->SetColor({ 1, 0, 0, 1 });

    std::shared_ptr<material_t> color = std::make_shared<material_t>();
    color->albedo = color3_t{ 1.6, 1.6, 0.5 };
    color->specular = color3_t{ 1 };
    color->shininess = 105.0f;
    
    std::shared_ptr<material_t> red = std::make_shared<material_t>();
    red->albedo = color3_t{ 1, 0, 0 };
    red->specular = color3_t{ .8f };
    red->shininess = 106.0f;

    

    std::vector<std::unique_ptr<Actor>> actors;
    for (int i = 0; i < 1; i++)
    {
        //Transform transform1{ { randomf(-10.0f, 15.0f), randomf(115.0f, 300.0f), randomf(-100.0f, -10.0f) }, glm::vec3{0, 0, 0}, glm::vec3{ randomf(2, 30) } };
        Transform transform1{ glm::vec3{ -5, 0, 0 }, glm::vec3{0, 0, 0}, glm::vec3{ 3 } };
        std::unique_ptr<Actor> actor1 = std::make_unique<Actor>(transform1, model, color);
        
        actors.push_back(std::move(actor1));
    }
    for (int i = 0; i < 1; i++)
    {
        //Transform transform2{ { randomf(-10.0f, 15.0f), randomf(115.0f, 300.0f), randomf(-100.0f, -10.0f) }, glm::vec3{0, 0, 0}, glm::vec3{ randomf(2, 30) } };
        Transform transform2{ glm::vec3{ 5, 0, 0 }, glm::vec3{0, 0, 0}, glm::vec3{ 3 } };
        std::unique_ptr<Actor> actor2 = std::make_unique<Actor>(transform2, model, red);
        
        actors.push_back(std::move(actor2));
    }


#pragma endregion

    bool quit = false;
    while (!quit)
    {
        time.Tick();
        input.Update();

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
        framebuffer.DrawImage(0, 30, image);

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

        int mx, my;
        SDL_GetMouseState(&mx, &my);
#pragma region MouseTracking

        //framebuffer.DrawLinearCurve(100, 100, 200, 200, { 255, 255, 255, 255 });
        ////framebuffer.DrawQuadraticCurve(100, 200, mx, my, 300, 200, { 255, 0, 255, 255 });
        //framebuffer.DrawCubicSpline(100, 200, 100, 100, 200, 100, 200, 200, { 255, 0, 0, 255 });

        //int x, y;
        //CubicPoint(300, 400, 300, 100, mx, my, 600, 400, t, x, y);
        //framebuffer.DrawRect(x - 20, y - 20, 100, 100, { 255, 0, 0, 255 });

#pragma region SetBlendModes

        SetBlendMode(BlendMode::Normal);
        //framebuffer.DrawImage(100, 100, image);
        SetBlendMode(BlendMode::Normal);
        //framebuffer.DrawImage(mx, my, ImageAlpha);

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

            cameraTransform.rotation.y += input.GetMouseRelative().x * 0.55f;
            cameraTransform.rotation.x += input.GetMouseRelative().y * 0.55f;

            glm::vec3 offset = cameraTransform.GetMatrix() * glm::vec4{ direction, 0 };

            cameraTransform.position += offset * 75.0f * time.GetDeltaTime();

        }
        else
        {
            input.SetRelativeMode(false);
        }

        camera.SetView(cameraTransform.position, cameraTransform.position + cameraTransform.GetForward());
        Shader::uniforms.view = camera.GetView();

        for (auto& actor : actors)
        {
            actor->GetTransform().rotation.y += time.GetDeltaTime() * 90;
            actor->Draw();
        }
#pragma endregion



        framebuffer.Update();

        // show screen
        renderer = framebuffer;
        SDL_RenderPresent(renderer.m_renderer);


    }

    return 0;
}