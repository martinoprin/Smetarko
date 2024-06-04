#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <time.h>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	bool running() { return isRunning; }
	bool GetPaused() { return paused; }
	void render();
	void clean();

	static SDL_Renderer* renderer;

private:
	char name[20] = "Vegovec";

	bool isRunning = false;
	bool paused = false;
	int cnt = 0;
	SDL_Window* window;
};
