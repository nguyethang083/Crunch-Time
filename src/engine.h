#ifndef ENGINE_H
#define ENGINE_H
#include "texture.h"
#include "Text.h"
#include "timer.h"

//Candies in squares
enum Candies{Destroyed, Red, Green, Blue, Orange, Pink, Gold, Total};

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
        Text score;

        //Timer
        Timer timer;
        Texture timerTexture;
        Text times;

         //Game font;
        Text scoreText;
        Text timeText;

        //Game state texture
        Texture startTexture;
        Texture endTexture;

        //Update screen
        void render();
};

#endif