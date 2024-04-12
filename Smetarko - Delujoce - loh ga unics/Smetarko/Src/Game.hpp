#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "vector"


GameObject* player;
GameObject* pesek;
std::vector<GameObject*> enemies;
std::vector<GameObject*> trash;



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
	player = new GameObject("assets/player.png", 0); 
	pesek = new GameObject("assets/pesek2.png", 2);

	for(int i = 0; i < 10; i++) {
		trash.push_back(new GameObject("assets/trash.png", 0));
	}
	for (int i = 0; i < 5; i++) {
		enemies.push_back(new GameObject("assets/enemy.png", 1));
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
	pesek->UpdatePesek();

	for (int i = trash.size() - 1; i >= 0; i--) {
		trash[i]->Update();
		if (checkCollision(player->getRect(), trash[i]->getRect())) {
			delete trash[i];
			trash.erase(trash.begin() + i);
		}
	}
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update();
		if (checkCollision(player->getRect(), enemies[i]->getRect())) {
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
	}
}



void Game::render()
{
	SDL_RenderClear(renderer);
	pesek->Render();
	player->Render();

	for(int i = 0; i < trash.size(); i++) 
	{trash[i]->Render();}

	for (int i = 0; i < enemies.size(); i++)
	{enemies[i]->Render();}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}