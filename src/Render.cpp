#include "Render.h"
#include <cmath>
#include "Errors.h"


void  Render::SDL_RenderFillCircle( int centerX, int centerY, int radius)
{
    for (int y = -radius; y <= radius; ++y)
    {
        int dx = static_cast<int>(std::sqrt(radius * radius - y * y)); // Calculate x extent for the given y
        SDL_RenderDrawLine(renderer, centerX - dx, centerY + y, centerX + dx, centerY + y);
    }
}

int Render::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {

    Uint32 flags = SDL_WINDOW_OPENGL;

    if (currentFlags & INVISIBLE) {
        flags |= SDL_WINDOW_HIDDEN;
    }

    if (currentFlags & FULLSCREEN) {
        flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
    }

    if (currentFlags & BORDERLESS) {
        flags |= SDL_WINDOW_BORDERLESS;
    }

    _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);

    renderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
    
    return 0;
}

void Render::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

}
void Render::present() {
    SDL_RenderPresent(renderer);

}

int Render::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(_sdlWindow);
    SDL_Quit();

    return 0;

}

void Render::renderParticle(int x, int y, Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderFillCircle(x, y, PARTICLE_RADIUS);
}
