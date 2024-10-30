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


    srand((unsigned int)time(NULL));

    Time time;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", 800, 600);

    SetBlendMode(BlendMode::Normal);

    Framebuffer framebuffer(renderer, renderer.m_width, renderer.m_height);

    Camera camera{ 70.0f, framebuffer.m_width / (float)framebuffer.m_height };
    camera.SetView({ 0, 0, -20 }, { 0, 0, 0 });

    Scene scene;

    std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
    auto object = std::make_unique<Sphere>(glm::vec3{ 0, 0, 0 }, 2.0f, material);
    scene.AddObject(std::move(object));


    std::shared_ptr<Material> grey = std::make_shared<Metal>(color3_t{ 0.5f }, 0.0f);
    std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
    std::shared_ptr<Material> blue = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    std::shared_ptr<Material> idk = std::make_shared<Dielectric>(color3_t{ 0, 1, 1 }, 20.4f);
    std::shared_ptr<Material> blu = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

    std::vector<std::shared_ptr<Material>> materials = { red, blue };

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, -1, 0 }, glm::vec3{ 0, 1, 0 }, grey);
    scene.AddObject(std::move(plane));

    for (int i = 0; i < 5; i++)
    {
        auto sphere = std::make_unique<Sphere>(random(glm::vec3{ -10 }, glm::vec3{ 10 }), randomf(1, 2), materials[random(2)]);
        scene.AddObject(std::move(sphere));
    }

    // render scene
    //framebuffer.Clear(ColorConvert(color4_t{ 0.25f, 0, 0, 1 }));
    scene.Render(framebuffer, camera, 2, 3);
    framebuffer.Update();

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

        

        // show screen
        renderer = framebuffer;
        SDL_RenderPresent(renderer.m_renderer);


    }

    return 0;
}
