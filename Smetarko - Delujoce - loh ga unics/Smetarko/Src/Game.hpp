#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "vector"


GameObject* player;
GameObject* enemy;
std::vector<GameObject*> enemies;



SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 176, 196, 255);
		}

		isRunning = true;
	}
	player = new GameObject("assets/player.png"); //main character
	enemy = new GameObject("assets/enemy.png"); //enemy character

	for(int i = 0; i < 10; i++) {
		enemies.push_back(new GameObject("assets/trash.png"));
	}
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	player->UpdateMovement();
	enemy->Update();
	for(int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update();
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	player->Render();
	enemy->Render();
for(int i = 0; i < enemies.size(); i++) {
		enemies[i]->Render();
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}