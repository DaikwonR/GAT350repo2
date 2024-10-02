#include "Renderer.h"

// create renderer
SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

//while (true)
//{
//    // clear screen
//    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
//    SDL_RenderClear(renderer);
//
//    // show screen
//    SDL_RenderPresent(renderer);
//}

void Renderer::Initialize()
{
    // initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }
}

void Renderer::CreateWindow(const std::string& name, int width, int height)
{
    // create window
        // returns pointer to window if successful or nullptr if failed
        SDL_Window * window = SDL_CreateWindow("Game Engine",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600,
            SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
        SDL_Quit();
    }
        
}

void Renderer::CopyFrameBuffer(const Framebuffer& framebuffer)
{
    SDL_RenderCopy(m_renderer, framebuffer.m_texture, NULL, NULL);
}

void Renderer::operator=(const Framebuffer& framebuffer)
{
    SDL_RenderCopy(m_renderer, framebuffer.m_texture, NULL, NULL);
}
