#include "common.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

bool gameStarted = false; 
bool gameover = false;
bool pressed = false;
bool selected = false;

Sint32 highscore;