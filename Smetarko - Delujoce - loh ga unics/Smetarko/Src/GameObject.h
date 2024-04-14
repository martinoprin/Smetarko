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

	int smer;
	int cas;

public:
	GameObject(const char* textureSheet, int type);
	~GameObject(){}

	SDL_Rect getRect()
	{return destRect;}


	void UpdateMovement();
	void UpdateSmeti();
	void UpdatePesek();
	void Update();
	void Render();

	bool isSea() const { return isSea_; }
	void SetIsSea(bool sea) { isSea_ = sea; }

};

bool checkCollision(SDL_Rect a, SDL_Rect b);