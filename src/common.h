#ifndef COMMON_H
#define COMMON_H
#include <SDL.h>
#include <string>

extern SDL_Window* window;
extern SDL_Renderer* renderer;

//Game state
extern bool gameover;

//Check if a candy was selected
extern bool pressed, selected;

//High score
extern Sint32 highscore;

#endif