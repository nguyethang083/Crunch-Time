#include "engine.h"
#include <bits/stdc++.h>

Engine::Engine() : WINDOW_WIDTH(800), WINDOW_HEIGHT(600), TITLE("Crunch Time") {
    time_t current = time(NULL);
    srand(current);
    if(!init()) {
        Error("Unable to init Engine");
    }
}

Engine::~Engine() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
}

bool Engine::init() {
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        LogSDL("SDL_Init");
        success = false; 
    }

    window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        LogSDL("CreateWindow");
        success = false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(renderer == NULL) {
        LogSDL("CreateRenderer");
        success = false;
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    
    return success;
}