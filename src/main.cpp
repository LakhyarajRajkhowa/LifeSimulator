#include <Windows.h>

#define SDL_MAIN_HANDLED


#include <SDL2/SDL.h>


#include "Simulator.h"

int main() {
	Simulator simulator;
	simulator.run();
}