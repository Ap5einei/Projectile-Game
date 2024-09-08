#include "Particle.h"

Particle::Particle(double p_x, double p_y, int p_radius, int p_color[4], double p_velocityX, double p_velocityY) {
	x = p_x;
	y = p_y;

	radius = p_radius;

	r = p_color[0];
	g = p_color[1];
	b = p_color[2];
	a = p_color[3];

	velocityX = p_velocityX;
	velocityY = p_velocityY;
}

void Particle::draw(SDL_Renderer* renderer) const {
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	for (int dy = -radius; dy <= radius; ++dy) {
		int width = SDL_sqrt(radius * radius - dy * dy) * 2;
		int startX = x - width / 2;
		int endX = startX + width;
		int currentY = y + dy;

		SDL_RenderDrawLine(renderer, startX, currentY, endX, currentY);
	}
}


void Particle::update() {
	x += velocityX;
	y += velocityY;
}

int Particle::getAlpha() {
	return a;
}
void Particle::setAlpha(int dAlpha) {
	a += dAlpha;
}