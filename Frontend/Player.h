#pragma once
 
#include<SDL.h>
#include "../../SDL-VisualStudio/include/SDL_render.h"

class Player{
public:
	Player(double p_x, double p_y, int p_radius, int p_color[4]);

	void draw(SDL_Renderer* renderer) const;

private:
	double x, y;
	int radius;
	int r, g, b, a;
};