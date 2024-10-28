// Ray Tracer Main

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
#include "Source\Tracer.h"
#include "Source\Scene.h"
#include "Source\Plane.h"


int main(int argc, char* argv[])
{

#pragma region Class Declarations

    Time time;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", 800, 600);

    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(renderer, renderer.m_width, renderer.m_height);

    Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height };
    camera.SetView({ 0, 0, -5 }, { 0, 0, 0 });

    Scene scene;

    std::shared_ptr<Material> material = std::make_shared<Material>(color3_t{ 1, 0, 0 });
    auto object = std::make_unique<Sphere>(glm::vec3{ 0, 0, 0 }, 2.0f, material);

    scene.AddObject(std::move(object));

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, material);
    scene.AddObject(std::move(plane));

    std::shared_ptr<Material> grey = std::make_shared<Material>(color3_t{ 0.5f });
    std::shared_ptr<Material> red = std::make_shared<Material>(color3_t{ 1, 0, 0 });
    std::shared_ptr<Material> blue = std::make_shared<Material>(color3_t{ 0, 0, 1 });

    std::vector<Sphere> spheres;

    //auto object = std::make_unique<Sphere>(random(glm::vec3{ -10 }, glm::vec3{ 10 }, random(1, 20), material));
    scene.AddObject(std::move(object));

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, -5, 0 }, glm::vec3{ 0, 1, 0 }, grey);
    scene.AddObject(std::move(plane));



#pragma endregion

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

        framebuffer.Clear(ColorConvert(color4_t{ 0.25f, 0, 0, 1 }));

        glm::vec3 posMin = glm::vec3(-10.0f, -10.0f, -10.0f);
        glm::vec3 posMax = glm::vec3(10.0f, 10.0f, 10.0f);
        float radMin = 0.5f;
        float radMax = 2.0f;

        for (int i = 0; i < 5; i++)
        {
            //spheres.begin
        }
        scene.Render(framebuffer, camera);

        framebuffer.Update();

        // show screen
        renderer = framebuffer;
        SDL_RenderPresent(renderer.m_renderer);


    }

    return 0;
}
