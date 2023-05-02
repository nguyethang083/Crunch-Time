#include "common.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool gameStarted = false; 
bool gameover = false;
bool pressed = false;
bool selected = false;

bool selectChange = false;

int gameMode = 0;
int timeMode = 1;

Sint32* highscore = 0;