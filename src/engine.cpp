#include "engine.h"
#include "log.h"
#include <random>

Engine::Engine() : WINDOW_WIDTH(800), WINDOW_HEIGHT(600), TITLE("Crunch Time") {
    savedBoard.resize(8, vector<int>(8));
    success = true; 
    if(!init()) {
        Error("Unable to init Engine");
        exit();
    } else if(!initTexture()) {
        Error("Unable to load Textures");
        exit();
    } else if(!initFont()) {
        Error("Unable to load Fonts!");
        exit();
    } else if(!initSound()) {
        Error("Unable to load Sounds!");
        exit();
    }
    else initSave();
}

Engine::~Engine() {
    if(!save()) {
        Error("Your data will not be saved!");
    }
    exit();
}

bool Engine::init() {
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        LogSDL("SDL_Init");
        success = false; 
    }

    if(TTF_Init() == -1) {
        LogTTF("TTF_Init");
        success = false;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        LogMixer("Mixer_OpenAudio");
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

    SDL_Surface *cursorSurface = IMG_Load("assets/cursor.png");
    if(cursorSurface == NULL) {
        LogIMG("IMG_Load");
        success = false;
    }
    cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
    if (cursor == NULL) {
        LogSDL("CreateColorCursor");
        success = false;
    }
    SDL_FreeSurface(cursorSurface);
    SDL_SetCursor(cursor);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
		Error("Warning: Linear texture filtering not enabled!");
    }
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
        hintTexture.loadFile("assets/hint.png") &&
        scoreTexture.loadFile("assets/play button.png") && 
        timerTexture.loadFile("assets/timer bg.png") &&
        highlightTexture.loadFile("assets/highlight.png") &&
        exitTexture.loadFile("assets/exit.png") &&
        startTexture.loadFile("assets/start_bg_01.png") &&
        endTexture.loadFile("assets/endBackground.png"))
    return true;

    else return false;
}

bool Engine::initFont() {
    //Open font
    if( !continueText.openFont(30) || !newGameText.openFont(30) || !gameModeText.openFont(25) || !timeModeText.openFont(20) || 
        !scoreText.openFont(30) || !highscoreText.openFont(30) || !timeText.openFont(30) || !scores.openFont(35) || 
        !highscores.openFont(35) || !times.openFont(75) || !startNotice.openFont(100))
    return false;

    //Load static text
    else if(!continueText.loadText("Continue") || !newGameText.loadText("New Game") || !scoreText.loadText("score") || 
            !highscoreText.loadText("high score") || !timeText.loadText("time") || !startNotice.loadText("START"))
        return false;

    else return true;
}
bool Engine::initSound() {
    if (!music.loadMusic("assets/sounds/music.mp3") || !matchSFX[0].loadSFX("assets/sounds/match1.ogg") ||
        !matchSFX[1].loadSFX("assets/sounds/match2.ogg") || !matchSFX[2].loadSFX("assets/sounds/match3.ogg") ||
        !startSFX.loadSFX("assets/sounds/gamestart.ogg") || !endSFX.loadSFX("assets/sounds/gameover.ogg"))
        return false;

        else return true;
}

void Engine::initSave() {
    SDL_RWops* save = SDL_RWFromFile("save.bin", "r+b");
    if(save == NULL) {
        Error("Warning: Unable to open save file!");
        //Initialize data
        for(int i = 0; i < Total_Mode; i++) {
            for(int j = 0; j < Total_Time; j++) {
                savedHighscore[i][j] = 0;  
            }
        }   
    }
    //File exists
    else {
        //Load data
        for(int i = 0; i < Total_Mode; i++) {
            for(int j = 0; j < Total_Time; j++) {
                SDL_RWread(save, &savedHighscore[i][j], sizeof(Sint32), 1);
            }
        }
        SDL_RWread(save, &forceQuit, sizeof(bool), 1);
        if(forceQuit) {
            SDL_RWread(save, &savedTime, sizeof(Uint32), 1);
            SDL_RWread(save, &savedScore, sizeof(Sint32), 1);
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    SDL_RWread(save, &savedBoard[i][j], sizeof(int), 1);
                }
            }
        }
        //Close file handler
        SDL_RWclose(save);
    }
}

bool Engine::save() {
    SDL_RWops* save = SDL_RWFromFile("save.bin", "r+b");
    if(save == NULL) {
        //Create file for writing
        save = SDL_RWFromFile("save.bin", "w+b");
    }
    if(save != NULL) {
        //Write to save file
        for(int i = 0; i < Total_Mode; i++) {
            for(int j = 0; j < Total_Time; j++) {
                SDL_RWwrite(save, &savedHighscore[i][j], sizeof(Sint32), 1);
            }
        }
        SDL_RWwrite(save, &forceQuit, sizeof(bool), 1);
        if(forceQuit) {
            SDL_RWwrite(save, &savedTime, sizeof(Uint32), 1);
            SDL_RWwrite(save, &savedScore, sizeof(Sint32), 1);
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    SDL_RWwrite(save, &savedBoard[i][j], sizeof(int), 1);
                }
            }
        }
        //Close file handler
        SDL_RWclose(save);
    } else {
        LogSDL("Save");
        return false;
    }
    return true;
}

void Engine::exit() {
    SDL_FreeCursor(cursor);
    cursor = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    Mix_Quit();
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int Engine::getRandom() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, Total - 1);
    return dist(rng);
}

void Engine::render() {
    SDL_RenderPresent(renderer);
}