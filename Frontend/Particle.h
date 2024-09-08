#pragma once

#include<SDL.h>
#include "../../SDL-VisualStudio/include/SDL_render.h"

class Particle {
public:
	Particle(double p_x, double p_y, int p_radius, int p_color[4], double p_velocityX, double p_velocityY);

	void draw(SDL_Renderer* renderer);
	void update();

	double getX();
	double getY();
	int getRadius();

	int getAlpha();
	void setAlpha(int dAlpha);

private:
	double x, y;
	int radius;
	int r, g, b, a;
	double velocityX, velocityY;
};