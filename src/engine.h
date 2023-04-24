#ifndef ENGINE_H
#define ENGINE_H
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "log.h"

//Candies in squares 
enum Candies{Destroyed, Red, Green, Blue, Orange, Pink, Total};

class Engine {
    private:
        //Window size
        const int WINDOW_WIDTH, WINDOW_HEIGHT;

        //Window title
        const std::string TITLE;

        //Init Engine
        bool init();

    protected:
        SDL_Window* window;
        SDL_Renderer* renderer;

    public: 
        Engine();
        ~Engine();

};

#endif