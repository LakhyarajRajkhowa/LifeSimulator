#pragma once
#include <SDL2/SDL.h>
#include <string>

#include "Color.h"

enum  windowFlags { INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4 };

const int PARTICLE_RADIUS = 3;
class Render
{
public:
	void  SDL_RenderFillCircle(int centerX, int centerY, int radius );
	int create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags);
	void render();
	void present();
	void renderParticle(int x, int y, Color color);
	int destroy();



private:
	SDL_Window* _sdlWindow;
	SDL_Renderer* renderer;
};

