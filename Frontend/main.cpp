#include "Game.h"
#include<SDL2/SDL.h>
#include "Game.cpp"

int main(int argc, char* argv[]) {
	Game game;

	game.run();
	game.cleanUp();
	return 0;
}