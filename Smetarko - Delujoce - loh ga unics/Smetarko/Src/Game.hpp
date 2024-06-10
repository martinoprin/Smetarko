#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "vector"


GameObject* player;
GameObject* pesek;
std::vector<GameObject*> enemies;
std::vector<GameObject*> trash;

int level[3][2] = {
	{5, 10},  //level 1
	{10, 20},  //level 2
	{15, 30}   //level 3
};
int lvl = 0;



SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;

	std::cout << "Enter player name: ";
	std::cin >> name;

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
	SDL_Surface* tempSurface = IMG_Load("assets/start_screen.png");
	    if (tempSurface == nullptr)
	    {
	        std::cerr << "Failed to load start screen image! IMG_Error: " << IMG_GetError() << std::endl;
	        isRunning = false;
	        return;
	    }
	    startScreenTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	    SDL_FreeSurface(tempSurface);
	
	    if (startScreenTexture == nullptr) 
	    {
	        std::cerr << "Failed to create start screen texture! SDL_Error: " << SDL_GetError() << std::endl;
	        isRunning = false;
	        return;
	    }
	
	player = new GameObject("assets/player.png", 0, 0); 
	pesek = new GameObject("assets/pesek2.png", 2, 0);

	for(int i = 0; i < level[lvl][1]; i++) {
		trash.push_back(new GameObject("assets/trash.png", 0, 0));
		//std::cout << level[0][1];
		//std::cout << level[1][1];
		//std::cout << level[2][1];

	}
	for (int i = 0; i < level[lvl][0]; i++) {
		enemies.push_back(new GameObject("assets/enemy.png", 1, 0));
		//std::cout << level[0][0];
		//std::cout << level[1][0];
		//std::cout << level[2][0];
	}
	
}

void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	if (showStartScreen) {
            	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
            		showStartScreen = false;
    	} 
	else {
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_F1]) {
		paused = !paused;
		//std::cout << paused << "\n";
		SDL_Delay(100);
	}

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
	if (showStartScreen) return;
	
	player->UpdateMovement();
	pesek->UpdatePesek();

	for (int i = 0; i < trash.size(); i++) {
		trash[i]->UpdateSmeti();
		if (checkCollision(player->getRect(), trash[i]->getRect())) {
			delete trash[i];
			trash.erase(trash.begin() + i);
		}
	}
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Update();
		if (enemies[i]->vrniXpos() == 875) {
			if(enemies[i]->vrniCas() == 0)
				trash.push_back(new GameObject("assets/trash.png", 4, enemies[i]->vrniYpos()));
		}
		if (checkCollision(player->getRect(), enemies[i]->getRect())) {
			delete enemies[i];
			enemies.erase(enemies.begin() + i);
		}
	}

	if (enemies.size() == 0 && trash.size() == 0 && lvl == 2)
		std::cout << "Konec igre";
	if(enemies.size() == 0 && trash.size() == 0 && lvl<2) {
		lvl++;


		for (int i = 0; i < level[lvl][0]; i++) {
			enemies.push_back(new GameObject("assets/enemy.png", 1, 0));
		}
		for (int i = 0; i < level[lvl][1]; i++) {
			trash.push_back(new GameObject("assets/trash.png", 0, 0));
		}
	}
	//enemies[0]->Follow(player);



	for (int i = 0; i < enemies.size(); i++) {
		for (int j = i + 1; j < enemies.size(); j++) {
			if (checkCollision(enemies[i]->getRect(), enemies[j]->getRect())) {
				//std::cout << "trk";
				enemies[i]->Snap(enemies[j]);
				if (checkCollision(player->getRect(), enemies[i]->getRect())) {
					std::cout << "mrtu si!!!!!!!!";
				}
			}
		}
	}
}



void Game::render()
{
	SDL_RenderClear(renderer);
	pesek->Render();
	player->Render();

	if (showStartScreen) {
        SDL_RenderCopy(renderer, startScreenTexture, NULL, NULL);
    	} else {

	for(int i = 0; i < trash.size(); i++) 
		{trash[i]->Render();}

	for (int i = 0; i < enemies.size(); i++)
		{enemies[i]->Render();}
	}
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyTexture(startScreenTexture);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


