#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "log.h"
#include <iostream>

using namespace std;

void LogSDL(const string msg) {
    cerr << msg << " Error: " << SDL_GetError() << '\n';
}

void LogIMG(const string msg) {
    cerr << msg << " Error: " << IMG_GetError() << '\n';
}

void LogTTF(const string msg) {
    cerr << msg << " Error: " << TTF_GetError() << '\n';
}

void Error(const string msg) {
    cerr << msg << '\n';
}