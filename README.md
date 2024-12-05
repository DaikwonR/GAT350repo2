# GAT350

![image](https://github.com/user-attachments/assets/5006d425-502f-41cd-bf53-503e84c31349)


## Table of Contents
- [Project Overview](#project-overview)
- [Software Rendering](#software_rendering)
- [Ray Tracing](#ray_tracing)
- [External Files](#external-files)
- [Third-Party Libraries](#third_party_libraries)
- [Build Instructions](#build_instructions)

- Welcome to my lovely description of how I learned what software rendering was in both 2 and 3D!

## Project Overview
- For this solution I was able to implement rasterization techniques, such as building wireframes that invluded drawing lines and conjoining triangles to build and display models to be rendered in the scene.
- I was able to handle image processing to display as backgrounds but also to show how transparency or colorin works within imaging.
- To expand on my rasterization I was able to improve towards 3D rasterization using OpenGL in a c++ engine to render 3D objects in real time.

## software_rendering
- Functionality for 2D/3D software rendering, revolving around lighting and camera to eye positioning, and algorithms that effectively draw and can even fill in wireframes for objects being rendered to the console.

## ray_tracing
- This is more specifically ray tracing involving drawing to the console and 3D rendering. This is more developed object building and scene manipulation by adding enhanced detailed materialing for not just objects but also the background.
- Examples include: Metal detailing, Lambertian, Emissive, Dielectric, etc. however in this project we involved less filling of the wireframes and more so how they are placed in the scene.

## third_party_libraries
- We incorporated inumerable libraries to help us do spcific processing and algorithims.
- For example we need a MathUtils class to involved specifc circular processing. We used the "glm" library. OpenGL mathematics for vector, matrix, and transformations.
- STB image for loading .pngs

## build_instructions
- An example of how we needed to run on main page utilizing every class and library: #include <SDL.h>
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

- Then we build all of our non obj/png objects such as the camera, and if involved, the lights: Time time;

Renderer renderer;
renderer.Initialize();
renderer.CreateWindow("2D", 800, 600);

Input input;
input.Initialize();
input.Update();


SetBlendMode(BlendMode::Normal);

Camera camera(renderer.m_width, renderer.m_height);
camera.SetView(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0 });
camera.SetProjection(90.0f, 800.0f / 600, 0.1f, 200.0f);
Transform cameraTransform{ { 0, 0, -20 } };

Framebuffer framebuffer(renderer, 800, 600);
