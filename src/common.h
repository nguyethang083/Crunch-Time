#ifndef COMMON_H
#define COMMON_H
#include <SDL.h>
#include <string>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

//Game state
extern bool gameStarted, gameover;

//Check if a candy was selected
extern bool pressed, selected;

//Game mode
extern int gameMode;

//High score
extern Sint32* highscore;

#endif