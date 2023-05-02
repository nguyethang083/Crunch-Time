#ifndef ENGINE_H
#define ENGINE_H
#include "texture.h"
#include "Text.h"
#include "timer.h"
#include "Sound.h"

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

        //Init Sound
        bool initSound();

        void exit();

    public:
        Engine();
        ~Engine();

        Timer timer; 
        //Textures
        Texture boardTexture; //Board texture
        Texture candyTexture[Total]; //Candies textures
        Texture selectorTexture; //Selector texture
        Texture hintTexture; // Hint texture
        Texture scoreTexture; //Score texture
        Texture timerTexture; //Timer texture
        Texture startTexture; //Start screen texture
        Texture endTexture; //End screen texture

        //Texts
        Text score; //Score
        Text highscore; //High score
        Text times; //Remaing time
        Text scoreText; // "score" text
        Text highscoreText; //"high score" text
        Text timeText; // "time" text

        //Sounds
        Sound music;
        Sound startSFX;
        Sound endSFX;
        Sound matchSFX[3];

        //Update screen
        void render();
};

#endif