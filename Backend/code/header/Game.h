#pragma once 

#include <iostream>
#include<SDL2/SDL.h>
#include "../../../../../Dev/C++/SDL-VisualStudio/include/SDL_video.h"
#include "../../../../../Dev/C++/SDL-VisualStudio/include/SDL_render.h"

class Game {
public:
	Game();

	void run();
	void cleanUp();

private:
	double windowWidth = 1200;
	double windowHeight = 680;
	SDL_Window* window;
	SDL_Renderer* renderer;
};