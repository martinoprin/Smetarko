#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, bool type) {
    objTexture = TextureManager::LoadTexture(textureSheet);
    if(type == 1)
    {
        xpos = rand() % 76 * 5 + 855;   //160 * 5 = 800      850 - 50 = 800
		ypos = rand() % 135 * 5;        //134 * 5 = 670      720 - 50 = 670
		isFlipped = true;
    }

    else if (type == 0) 
    {
        xpos = rand() % 161 * 5;   //160 * 5 = 800      850 - 50 = 800
        ypos = rand() % 135 * 5;   //134 * 5 = 670      720 - 50 = 670
        isFlipped = true;
    }
    else if (type == 2) {
        xpos = 1230;
        ypos = 0;
    }
}

void GameObject::UpdateMovement() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W] && ypos > 0)
        ypos -= 5; // Up
    if (currentKeyStates[SDL_SCANCODE_S] && ypos < 670)
        ypos += 5; // Down
    if (currentKeyStates[SDL_SCANCODE_A] && xpos > 0) {
        xpos -= 5; // Left
        isFlipped = false;
    }
    if (currentKeyStates[SDL_SCANCODE_D] && xpos < 1230) {
        xpos += 5; // Right
        isFlipped = true;
    }
    if (xpos < 850) {
        if (!isSea_) { // ce je igralec prisel na morje
            objTexture = TextureManager::LoadTexture("assets/player.png");
            SetIsSea(true);
        }
    }
    else {
        if (isSea_) { // ce je igralec prisel na kopno
            objTexture = TextureManager::LoadTexture("assets/enemy.png");
            SetIsSea(false);
        }
    }


    srcRect.h = 100;
    srcRect.w = 100;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 2;
    destRect.h = srcRect.h / 2;

    //std::cout << "x:" << xpos << "\t";
    //std::cout << "y:" << ypos << std::endl;
}

void GameObject::Update() {
    srcRect.h = 100;
    srcRect.w = 100;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 2;
    destRect.h = srcRect.h / 2;

    //std::cout << xpos << std::endl;
    //std::cout << ypos << std::endl;
}

void GameObject::UpdatePesek() {
    srcRect.h = 100;
    srcRect.w = 100;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 2;
    destRect.h = srcRect.h / 2;
}



void GameObject::Render() {
    if (isFlipped)
        SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
