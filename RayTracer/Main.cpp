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
#include "Source\Triangle.h"

//void InitScene(Scene& scene);
//void InitScene01(Scene& scene, Camera& camera);
void InitScene02(Scene& scene, Camera& camera);
//void InitScene03(Scene& scene, Camera& camera);


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

	//Model model;

	//InitScene(scene);
	//InitScene01(scene, camera);
	InitScene02(scene, camera);
	//InitScene03(scene, camera);

	// render scene
	// framebuffer.Clear(ColorConvert(color4_t{ 0.25f, 0, 0, 1 }));
	scene.Update();
	scene.Render(framebuffer, camera, 110, 6);
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

void InitScene(Scene& scene)
{
	std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
	auto object = std::make_unique<Sphere>(glm::vec3{ 0, 0, 0 }, 2.0f, material);
	scene.AddObject(std::move(object));


	std::shared_ptr<Material> grey = std::make_shared<Metal>(color3_t{ 0.5f }, 0.0f);
	std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
	std::shared_ptr<Material> blue = std::make_shared<Emissive>(color3_t{ 0, 0, 1 }, 1.0f);
	std::shared_ptr<Material> idk = std::make_shared<Dielectric>(color3_t{ 0, 1, 1 }, 20.4f);
	std::shared_ptr<Material> blu = std::make_shared<Lambertian>(color3_t{ 0.5, 0, 1 });

	std::vector<std::shared_ptr<Material>> materials = { blu, idk };

	auto plane = std::make_unique<Plane>(Transform{ glm::vec3{ 0, -2, 0}, glm::vec3{ 0, 0, 0} }, grey);
	scene.AddObject(std::move(plane));

	for (int i = 0; i < 5; i++)
	{
		Transform transform = Transform{ glm::vec3{ random(glm::vec3{ -10.0f }, glm::vec3{ 10.0f })} };
		float rand1 = randomf(1.0f, 3.0f);
		int f1 = random((int)materials.size());
		auto mat = materials[f1];
		auto sphere = std::make_unique<Sphere>(transform, rand1, mat);
		scene.AddObject(std::move(sphere));
	}

	glm::vec3 v1{ -3.0f, 0.0f, 0.0f };
	glm::vec3 v2{ 0.0f, 3.0f, 0.0f };
	glm::vec3 v3{ 3.0f, 0.0f, 0.0f };

	auto triangle = std::make_unique<Triangle>(Transform{ glm::vec3{ 0, 4, 0 }, glm::vec3{ 0 }, glm::vec3{ 2 } }, v1, v2, v3, red);
	scene.AddObject(std::move(triangle));


	auto model = std::make_unique<Model>(Transform{ glm::vec3{ 0,4,0 } }, materials[random((int)materials.size())]);
	model->Load("cube.obj");
	scene.AddObject(std::move(model));

}

void InitScene02(Scene& scene, Camera& camera)
{
	camera.SetFOV(80.0f);
	camera.SetView({ 0, 0, -20 }, { 0, 0, 0 });

	//std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 1.8f, 0.2f, 0.5f });
	//auto object = std::make_unique<Sphere>(glm::vec3{ 0, 0, 8 }, 2.0f, material);
	//scene.AddObject(std::move(object));


	std::shared_ptr<Material> grey = std::make_shared<Metal>(color3_t{ 0.5f }, 0.0f);
	std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
	std::shared_ptr<Material> idk = std::make_shared<Dielectric>(color3_t{ 0, 0, 0 }, 25.4f);
	std::shared_ptr<Material> blu = std::make_shared<Lambertian>(color3_t{ 0.5, 0, 1 });
	std::shared_ptr<Material> white = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });

	std::shared_ptr<Material> blue = std::make_shared<Emissive>(color3_t{ 0, 0, 1 }, 1.0f);
	std::shared_ptr<Material> white2 = std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 20.0f);

	std::vector<std::shared_ptr<Material>> materials = { grey, idk };

	auto plane1 = std::make_unique<Plane>(Transform{ glm::vec3{ 10, 0, 0}, glm::vec3{ 0, 0, 90} }, green); // right
	auto plane2 = std::make_unique<Plane>(Transform{ glm::vec3{ -10, 0, 0}, glm::vec3{ 0, 0, 270} }, red); // left
	auto plane3 = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 10, 0}, glm::vec3{ 0, 0, 180} }, white); // top
	auto plane4 = std::make_unique<Plane>(Transform{ glm::vec3{ 0, -10, 0}, glm::vec3{ 0, 0, 0} }, white); // bottom
	auto plane5 = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 0, 10}, glm::vec3{ 270, 0, 0} }, white); // back
	scene.AddObject(std::move(plane1));
	scene.AddObject(std::move(plane2));
	scene.AddObject(std::move(plane3));
	scene.AddObject(std::move(plane4));
	scene.AddObject(std::move(plane5));

	// top light
	auto light = std::make_unique<Model>(Transform{ glm::vec3{ 0, 9.95, 0 }, glm::vec3{ 0, 0, 0} }, white2);
	light->Load("cube.obj");
	scene.AddObject(std::move(light));

	auto model = std::make_unique<Model>(Transform{ glm::vec3{ 0, 3, 0 } }, blue);
	model->Load("cube.obj");
	scene.AddObject(std::move(model));
}

void InitScene03(Scene& scene, Camera& camera)
{
	camera.SetFOV(80.0f);
	camera.SetView({ 0, 0, -20 }, { 0, 0, 0 });

	/* std::shared_ptr<Material> material = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });
	 auto object = std::make_unique<Sphere>(glm::vec3{ 0, 0, 0 }, 2.0f, material);
	 scene.AddObject(std::move(object));*/


	std::shared_ptr<Material> grey = std::make_shared<Metal>(color3_t{ 0.5f }, 0.0f);
	std::shared_ptr<Material> red = std::make_shared<Lambertian>(color3_t{ 1, 0, 0 });
	std::shared_ptr<Material> green = std::make_shared<Lambertian>(color3_t{ 0, 1, 0 });
	std::shared_ptr<Material> idk = std::make_shared<Dielectric>(color3_t{ 0, 0, 0 }, 25.4f);
	std::shared_ptr<Material> blu = std::make_shared<Lambertian>(color3_t{ 0.5, 0, 1 });
	std::shared_ptr<Material> white = std::make_shared<Lambertian>(color3_t{ 1, 1, 1 });

	std::shared_ptr<Material> blue = std::make_shared<Emissive>(color3_t{ 0, 0, 1 }, 1.0f);
	std::shared_ptr<Material> white2 = std::make_shared<Emissive>(color3_t{ 1, 1, 1 }, 20.0f);

	std::vector<std::shared_ptr<Material>> materials = { grey, idk };

	auto plane1 = std::make_unique<Plane>(Transform{ glm::vec3{ 10, 0, 0}, glm::vec3{ 0, 0, 90} }, green); // right
	auto plane2 = std::make_unique<Plane>(Transform{ glm::vec3{ -10, 0, 0}, glm::vec3{ 0, 0, 270} }, red); // left
	auto plane3 = std::make_unique<Plane>(Transform{ glm::vec3{ 0, 0, 10}, glm::vec3{ 270, 0, 0} }, idk); // middle

	scene.AddObject(std::move(plane1));
	scene.AddObject(std::move(plane2));
	scene.AddObject(std::move(plane3));

	glm::vec3 v1{ -3.0f, 0.0f, 0.0f };
	glm::vec3 v2{ 0.0f, 3.0f, 0.0f };
	glm::vec3 v3{ 3.0f, 0.0f, 0.0f };

	for (int i = 0; i < 2; i++)
	{
		auto model = std::make_unique<Model>(Transform{ glm::vec3{ -10, 0, 0 }, glm::vec3{ 0 }, glm::vec3{ 7 } }, blue);
		model->Load("suzanne.obj");
		scene.AddObject(std::move(model));

		auto triangle = std::make_unique<Triangle>(Transform{ glm::vec3{ 0, 6, 0 }, glm::vec3{ 0 }, glm::vec3{ 2 } }, v1, v2, v3, red);
		scene.AddObject(std::move(triangle));

	}

	auto torus = std::make_unique<Model>(Transform{ glm::vec3{ 2, 0, 0 }, glm::vec3{ 270, 0, 0}, glm::vec3{ 3 } }, white2);
	torus->Load("teapot.obj");
	scene.AddObject(std::move(torus));

	auto model = std::make_unique<Model>(Transform{ glm::vec3{ 0, 0, 0 } }, blue);
	model->Load("cube.obj");
	scene.AddObject(std::move(model));
}


void InitScene01(Scene& scene, Camera& camera)
{
	camera.SetFOV(20.0f);
	camera.SetView({ 13, 2, 3 }, { 0, 0, 0 });

	auto ground_material = std::make_shared<Lambertian>(color3_t(0.5f));
	scene.AddObject(std::make_unique<Plane>(Transform{ glm::vec3{ 0 } }, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = randomf();
			glm::vec3 center(a + 0.9 * randomf(), 0.2, b + 0.9 * randomf());

			if ((center - glm::vec3(4, 0.2, 0)).length() > 0.9) {
				std::shared_ptr<Material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
					sphere_material = std::make_shared<Lambertian>(albedo);
					scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = HSVtoRGB(randomf(0, 360), 1.0f, 1.0f);
					auto fuzz = randomf(0.0f, 0.5f);
					sphere_material = std::make_shared<Metal>(albedo, fuzz);
					scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
				}
				else {
					// glass
					sphere_material = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
					scene.AddObject(std::make_unique<Sphere>(Transform{ center }, 0.2f, sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<Dielectric>(color3_t{ 1 }, 1.5f);
	scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 0, 1, 0 } }, 1.0f, material1));

	auto material2 = std::make_shared<Lambertian>(color3_t(0.4f, 0.2f, 0.1f));
	scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ -4, 1, 0 } }, 1.0f, material2));

	auto material3 = std::make_shared<Metal>(color3_t(0.7f, 0.6f, 0.5f), 0.0f);
	scene.AddObject(std::make_unique<Sphere>(Transform{ glm::vec3{ 4, 1, 0 } }, 1.0f, material3));
}