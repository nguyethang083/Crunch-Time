#include <SDL.h>
#include <SDL_image.h>
#include "log.h"
#include <iostream>

using namespace std;

void Log::SDL(const string& msg) {
    cout << msg << " Error: " << SDL_GetError();
}

void Log::IMG(const string& msg) {
    cout << msg << " Error: " << IMG_GetError();
}