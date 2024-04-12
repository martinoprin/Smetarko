#pragma once

#include "Game.h"

class GameObject
{
private:
	int xpos{};
	int ypos{};
	int width{};
	int height{};

	bool isFlipped = false;
	bool isSea_ = false;

	SDL_Texture* objTexture;
	SDL_Rect srcRect{}, destRect{};

public:
	GameObject(const char* textureSheet, bool type);
	~GameObject(){}

	SDL_Rect getRect()
	{return destRect;}


	void UpdateMovement();
	void UpdatePesek();
	void Update();
	void Render();

	bool isSea() const { return isSea_; }
	void SetIsSea(bool sea) { isSea_ = sea; }

};

bool checkCollision(SDL_Rect a, SDL_Rect b);