#pragma once

#include "Game.h"

class GameObject
{
public:
	GameObject(const char* textureSheet);
	~GameObject(){}

	void Update();
	void Render();

private:
	int xpos{};
	int ypos{};
	bool isFlipped = false;

	SDL_Texture* objTexture;
	SDL_Rect srcRect{}, destRect{};
};