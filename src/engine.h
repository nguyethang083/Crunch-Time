#ifndef ENGINE_H
#define ENGINE_H
#include "texture.h"
#include "timer.h"

//Candies in squares
enum Candies{Destroyed, Red, Green, Blue, Orange, Pink, Total};

class Engine {
    private:
        //Window size
        const int WINDOW_WIDTH, WINDOW_HEIGHT;

        //Window title
        const std::string TITLE;
        
        bool success;

        //Init Engine
        bool init();

        //Init Texture
        bool initTexture();

        //Init font
        bool initFont();

        void exit();

    public:
        Engine();
        ~Engine();

        //Board texture
        Texture boardTexture;

        //Canides textures
        Texture candyTexture[Total];

        //Selector texture
        Texture selectorTexture;

        //Score texture
        Texture scoreTexture;
        Texture scoreFont;

        //Timer
        Timer timer;
        Texture timerTexture;
        Texture timerFont;

         //Game font;
        Texture gFont[2];

        void render();

        void renderClear(SDL_Rect* rect);
};

#endif