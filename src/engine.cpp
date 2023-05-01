#include "engine.h"
#include "log.h"
#include <bits/stdc++.h>

Engine::Engine() : WINDOW_WIDTH(800), WINDOW_HEIGHT(600), TITLE("Crunch Time") {
    srand(time(NULL));
    success = true; 
    if(!init()) {
        Error("Unable to init Engine");
        exit();
    } else if(!initTexture()) {
        Error("Unable to load Textures");
        exit();
    }
    else if(!initFont()) {
        Error("Unable to load Font!");
        exit();
    }
}

Engine::~Engine() {
    exit();
}

bool Engine::init() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        LogSDL("SDL_Init");
        success = false; 
    }

    if(TTF_Init() == -1) {
        LogTTF("TTF_Init");
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

bool Engine::initTexture() {
    if (boardTexture.loadFile("assets/game_background_4.png") &&
        candyTexture[Red].loadFile("assets/red.jpg") &&
        candyTexture[Green].loadFile("assets/green.jpg") &&
        candyTexture[Blue].loadFile("assets/blue.jpg") &&
        candyTexture[Orange].loadFile("assets/orange.jpg") &&
        candyTexture[Pink].loadFile("assets/pink.jpg") &&
        candyTexture[Gold].loadFile("assets/gold.jpg") &&
        selectorTexture.loadFile("assets/selector.png") && 
        scoreTexture.loadFile("assets/play button.png") && 
        timerTexture.loadFile("assets/timer bg.png") &&
        startTexture.loadFile("assets/start_bg_01.png") &&
        endTexture.loadFile("assets/endBackground.png"))
    return true;

    else return false;
}

bool Engine::initFont() {
    //Open font
    if (!scoreText.openFont(30) || !timeText.openFont(30) || !score.openFont(35) ||
        !times.openFont(75))
    return false;

    //Load static text
    else if(!scoreText.loadText("score") || !timeText.loadText("time"))
    return false;

    else return true;
}

void Engine::exit() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

void Engine::render() {
    SDL_RenderPresent(renderer);
}