/* #include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SPRITE_WIDTH = 431;
const int SPRITE_HEIGHT = 400;
const int SPRITE_COUNT = 50;
const int SPRITE_ROWS = 8;
const int SPRITE_COLUMNS = 7;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* spriteSheet = nullptr;

bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("SDL2 Sprite Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }

    return true;
}

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Texture* texture = nullptr;
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (surface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(surface);
    return texture;
}

void close() {
    SDL_DestroyTexture(spriteSheet);
    spriteSheet = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = nullptr;
    renderer = nullptr;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        std::cerr << "Failed to initialize!" << std::endl;
        return 1;
    }

    spriteSheet = loadTexture("assets/image/compact ver.png");
    if (spriteSheet == nullptr) {
        std::cerr << "Failed to load sprite sheet!" << std::endl;
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    int currentSprite = 0;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

		int currentRow = currentSprite / SPRITE_COLUMNS;
    	int currentColumn = currentSprite % SPRITE_COLUMNS;

        SDL_Rect srcRect = {currentColumn * SPRITE_WIDTH, currentRow * SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
    	SDL_Rect dstRect = {(SCREEN_WIDTH - SPRITE_WIDTH) / 2, (SCREEN_HEIGHT - SPRITE_HEIGHT) / 2, SPRITE_WIDTH, SPRITE_HEIGHT};

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, spriteSheet, &srcRect, &dstRect);
        SDL_RenderPresent(renderer);

        currentSprite = (currentSprite + 1) % SPRITE_COUNT;
        SDL_Delay(100); // Adjust the delay for the desired animation speed
    }

    close();
    return 0;
} */