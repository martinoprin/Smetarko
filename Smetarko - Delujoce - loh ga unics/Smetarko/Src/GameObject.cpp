#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y) {
    objTexture = TextureManager::LoadTexture(textureSheet);
    xpos = x;
    ypos = y;
    isFlipped = false; // Initially not flipped
}

void GameObject::Update() {
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W] && ypos != 0)
        ypos -= 5; // Up
    if (currentKeyStates[SDL_SCANCODE_S] && ypos != 670)
        ypos += 5; // Down
    if (currentKeyStates[SDL_SCANCODE_A] && xpos != 0) {
        xpos -= 5; // Left
        isFlipped = false;
    }
    if (currentKeyStates[SDL_SCANCODE_D] && xpos != 1230) {
        xpos += 5; // Right
        isFlipped = true;
    }

    srcRect.h = 100;
    srcRect.w = 100;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w / 2;
    destRect.h = srcRect.h / 2;

    std::cout << "x:" << xpos << "\t";
    std::cout << "y:" << ypos << std::endl;
}

void GameObject::Render() {
    if (isFlipped)
        SDL_RenderCopyEx(Game::renderer, objTexture, &srcRect, &destRect, 0, NULL, SDL_FLIP_HORIZONTAL);
    else
        SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
 