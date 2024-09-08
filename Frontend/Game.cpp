#include"Game.h"
 #include"SDL_ttf.h"  
#include "../../../../../Dev/C++/SDL-VisualStudio/include/SDL_render.h"
#include "../../../../../Dev/C++/SDL-VisualStudio/include/SDL_video.h"
#include<chrono>
#include<cmath>
#include<iostream>
#include<random>
#include<SDL2/SDL.h>
#include<vector>
#include<string>

Game::Game() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		std::cout << "Epäonnistui lataamaan SDL";
	}

	if (TTF_init() != 0) {
		std::cout << "Failed to initialize SDL_TTF";
	}

	window = SDL_CreateWindow(
		"Projectile Shooter",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth,
		windowHeight,
		0
	);

	if (!window) {
		std::cout << "Epäonnistui lataamaan ikkunan";
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	if (!renderer) {
		std::cout << "Epäonnistui renderöimään";
	}

	font = TTF_OpenFont("Antrapo Font Demo.ttf", 30);
	if (!font) {
		std::cout << " failed to open font";
	}

}

void Game::run() {
	bool running = true;
	SDL_Event event;

	int playerColor[4] = { 255,255,255,255 };
	Player player(windowWidth / 2, windowHeight / 2, 10, playerColor);
	int projectileColor[4] = { 255,255,255,255 };

	std::vector<Projectile>projectiles;

	int enemyColor[4] = { 255, 0, 0, 255 };
	std::vector<Enemy>enemies;
	int enemyGenerationInterval = 1000;
    auto lastGenerationTime = std::chrono::high_resolution_clock::now();

	std::random_device rd;
	std::mt19937 generator(rd());

	std::vector<Particle> particles;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {

					if (playing) {
						int mouseX = event.button.x;
						int mouseY = event.button.y;

						double angleRadians = std::atan2(mouseY - windowHeight / 2, mouseX - windowWidth / 2);

						double velocityX = std::cos(angleRadians) / 2;
						double velocityY = std::cos(angleRadians) / 2;

						projectiles.emplace_back(windowWidth / 2, windowHeight / 2, 5, projectileColor, velocityX, velocityY);

						for (int i = 0; i < 16; i++) {

							if (std::abs(velocityX / i / 0.25) < abs(velocityX) && std::abs(velocityY / i / 0.25) < std::abs(velocityY) {
								particles.emplace_back(windowWidth / 2, windowHeight / 2, 3, particleColor, velocityX / i / 0 .25, randomVelocityY);
							}
						}
					}
					else {
						score = 0;
						enemies.clear();
						projectiles.clear();
						playing = true;
					}

				}
			}
		}

	
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		auto currentTime = std::chrono::high_resolution_clock::now();
		auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastGenerationTime).count();

		if (playing) {



			if (elapsedTime >= enemyGenerationInterval) {
				std::uniform_int_distribution<int>enemyRadiusDistribution(10, 30);
				int radius = enemyRadiusDistribution(generator);

				std::uniform_int_distribution<int>yDistribution(0, windowHeight);
				int randomY = yDistribution(generator);

				std::uniform_int_distribution<int>xDistribution(0, windowWidth
					int randomX = xDistribution(generator);

				std::uniform_int_distribution<int>randomDistribution(0, 1);
				int choice1 = randomChoiceDistribution(generator);
				int choice2 = randomChoiceDistribution(generator);

				double enemyX = (choice1 == 0) ? ((choice2 == 0) ? 0 - radius : windowWidth + radius) : randomX;
				double enemyY = (choice1 == 0) ? randomY : ((choice2 == 0) ? 0 - radius : windowHeight + radius);

				double angleRadians = std::atan2(windowHeight / 2 - enemyY, windowWidth / 2 - enemyX);

				double velocityX = std::cos(angleRadians) / 6;
				double velocityY = std::sin(angleRadians) / 6;

				std::uniform_int_distribution<int>enemyRadiusDistribution(10, 30);
				int r = colorDistribution(generator);
				int g = colorDistribution(generator);
				int b = colorDistribution(generator);

				enemyColor[0] = r;
				enemyColor[1] = g;
				enemyColor[2] = b;

				enemies.emplace_back(enemyX, enemyY, radius, enemyColor, velocityX, velocityY);
				lastGenerationTime = currentTime;

			}
			if (enemies.size() <= 3) {
				enemyGenerationInterval = 500;
			}

			else if (enemies.size() > 3 && enemies.size() < 7) {
                 enemyGenerationInterval = 1000;
			}
			else if (enemies.size() >= 7) {
				enemyGenerationInterval = 1500;
			}

			for (auto projectile = projectiles.begin(); projectile != projectiles.end();) {
				bool projectileRemoved = false;

				if (projectile->getX() < 0 || projectile->getX() > windowWidth) {
					projectileRemoved = true;
				}

				for (auto enemy = enemies.begin(); enemy != enemies.end();) {
					double distanceSquared = std::pow(projectile->getX(-enemy->getX() - enemy->getX(), 2.0) + std::pow(projectile->getY() - enemy->getY(), 2.0);
					int radiusSumSquared = std::pow(projectile->getRadius() + enemy->getRadius(), 2.0);

					if (distanceSquared <= radiusSumSquared) {

						score += 10;

						int particleColor[4] = { enemy->getR(), enemy->getG(), enemy->getB(),255 };
						for (int i = 0; i < 8; i++) {
							std::uniform_real_distribution<double> randomVelocityDistribution(-0.5, 0.5);
							double randomVelocityX = randomVelocityDistribution(generator);
							double randomVelocityY = randomVelocityDistribution(generator);

							particles.emplace_back(projectile->getX(), projectile->getY(), 3, particleColor, randomVelocityX, randomVelocityY);
						}

						if (enemy->getRadius() > 10) {
							enemy->setRadius(-10);
						}
						else {
							enemy = enemies.erase(enemy);
						}

						projectileRemoved = true;



					}
					else {
						++enemy;
					}
				}
				if (projectileRemoved) {
					projectile = projectiles.erase(projectile);
				}
				else {
					++projectile;
				}
			}

			for (auto enemy = enemies.begin(); enemy != enemies.end();) {
				double distanceSquared = std::pow(windowWidth / 2 - enemy->getX(), 2.0) + std::pow(windowHeight / 2 - enemy->getY(), 2.0);
				int radiusSumSquared = std::pow(10 + enemy->getRadius(), 2.0);

				if (distanceSquared <= radiusSumSquared) {

					playing = false;
				}

				++enemy
			}


			player.draw(renderer);

			for (Projectile& projectile : projectiles) {
				projectile.draw(renderer);
				projectile.update();
			}

			for (Enemy& enemy : enemies) {
				enemy.draw(renderer);
				enemy.update();
			}

			for (auto particle = particles.begin(); particle != particles.end();) {
				particle->draw(renderer);
				particle->update();

				particle->setAlpha(-1);
				if (particle->getAlpha() <= 0) {
					particle = particles.erase(particle);
				}
				else {
					++particle;
				}
			}

			scoreTextDest.x = 10;
			scoreTextDest.y = 10;
			scoreTextDest.w = 200;
			scoreTextDest.h = 50;

			SDL_Color textColor = { 255, 255, 255 };
			std::string scoreText = "Score: " + std::to_string(score);

			SDL_Surface* textSurface = TTF_RenderText_Solid(font, score.c_str(), textColor)
				if (!textSurface) {
					std::cout << "Failed to render" << std::endl;
				}

			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

			SDL_FreeSurface(textSurface);
			SDL_RenderCopy(renderer, textTexture, NULL, &scoreTextDest);
		}
		else {
			playTextDest.x = windowWidth / 2 - 200;
			playTextDest.y = windowHeight / 2 + 50;
			playTextDest.w = 400;
			playTextDest.h = 100;

			SDL_Color whiteColor = { 255, 255, 255 };

			SDL_Surface* playTextSurface = TTF_RenderText_Solid(font, "Click to play", whiteColor);
			if(!playTextSurface){
					std::cout << "Failed to render Text" << std::endl;
				}
			

			SDL_Texture* playTextTexture = SDL_CreateTextureFromSurface(renderer, playTextSurface);

			SDL_FreeSurface(playTextSurface);
			SDL_RenderCopy(renderer, playTextTexture, NULL, &playTextDest);

			scoreTextDest.x = windowWidth / 2 - 100;
			scoreTextDest.y = windowHeight / 2 - 50;
			scoreTextDest.w = 200;
			scoreTextDest.h = 100;

			SDL_Color textColor = { 255, 255, 255 };
			std::string scoreText = "Score: " + std::to_string(score);

			SDL_Surface* textSurface = TTF_RenderText_Solid(font, score.c_str(), textColor)
				if (!textSurface) {
					std::cout << "Failed to render" << std::endl;
				}

			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

			SDL_FreeSurface(textSurface);
			SDL_RenderCopy(renderer, textTexture, NULL, &scoreTextDest);
		
		}
		SDL_RenderPresent(renderer);
	}
}

void Game::cleanUp() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit(); 

}