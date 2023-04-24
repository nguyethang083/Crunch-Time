#include <SDL.h>
#include <SDL_image.h>
#include "log.h"
#include <iostream>

using namespace std;

void LogSDL(const char* msg) {
    cout << msg << " Error: " << SDL_GetError() << '\n';
}

void LogIMG(const char* msg) {
    cout << msg << " Error: " << IMG_GetError() << '\n';
}

void Error(const char* msg) {
    cout << msg;
}