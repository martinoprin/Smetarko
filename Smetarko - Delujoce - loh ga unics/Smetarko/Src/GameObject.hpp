#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int type, int yposs) {
    objTexture = TextureManager::LoadTexture(textureSheet);
    if(type == 1) //kopno
    {
        xpos = rand() % 76 * 5 + 855;   //160 * 5 = 800      850 - 50 = 800
		ypos = rand() % 135 * 5;        //134 * 5 = 670      720 - 50 = 670
		isFlipped = true;
    }

    else if (type == 0) //morje
    {
        xpos = rand() % 161 * 5;   //160 * 5 = 800      850 - 50 = 800
        ypos = rand() % 135 * 5;   //134 * 5 = 670      720 - 50 = 670
        isFlipped = true;
    }
    else if (type == 2) { //pozicija peska
        xpos = 1230;
        ypos = 0;
    }
    else if (type == 4) { //smeti - ki jih odvrze enemy
        xpos = 860;
        ypos = yposs;
    }
    smer = rand() % 4;
    cas = rand() % 100;

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

void GameObject::Update() { //enemy movement


    if (cas != 0) {
        switch (smer) {

        case 0:
            if (ypos > 0)
                ypos -= 1;
            break;

        case 1:
            if (ypos < 670)
                ypos += 1;
            break;

        case 2:
            if (xpos > 875) {
                xpos -= 1;
                isFlipped = false;
            }
            break;

        case 3:
            if (xpos < 1230) {
                xpos += 1;
                isFlipped = true;
            }
            break;
        }
        cas--;
    }
    else {
        smer = rand() % 4;
        cas = rand() % 100;
    }

    //std::cout << cas << std::endl;

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

void GameObject::UpdateSmeti() {

    xpos -= 0.5; // ce je ena gre dol


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
    srcRect.h = 720;
    srcRect.w = 425;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = 880; //855+25
    destRect.y = 0;
    destRect.w = srcRect.w;
    destRect.h = srcRect.h;
}



void GameObject::Render() {
    if (isFlipped)
        SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

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

    return true;
}

void GameObject::Follow(GameObject* target) {

    int dx = target->xpos - this->xpos;
    int dy = target->ypos - this->ypos;

    float length = sqrt(dx * dx + dy * dy);
    if (length > 0) {
        dx /= length;
        dy /= length;
    }

    this->xpos += dx;
    this->ypos += dy;

    this->isFlipped = dx > 0;
}

void GameObject::Snap(GameObject* target) {

    this->xpos = target->xpos;
    this->ypos = target->ypos;
}