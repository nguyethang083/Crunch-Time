#ifndef ENGINE_H
#define ENGINE_H
#include <SDL.h>
#include <string>
#include <log.h>

//Candies in squares 
enum Candies{Destroyed, Red, Green, Blue, Orange, Pink, Total};

class Engine {
    private:
        const int WINDOW_WIDTH, WINDOW_HEIGHT;
        const std::string TITLE;
        SDL_Surface* icon;
        bool init();
    public:
        SDL_Window* window;
        SDL_Renderer* renderer;
        Engine();
        ~Engine();

};

#endif