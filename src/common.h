#ifndef COMMON_H
#define COMMON_H
#include <SDL.h>

//Candies in squares
enum Candies{Destroyed, Red, Green, Blue, Orange, Pink, Total};

extern SDL_Window* window;
extern SDL_Renderer* renderer;

#endif