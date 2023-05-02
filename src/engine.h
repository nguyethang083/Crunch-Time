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
        
        //Custom mouse cursor
        SDL_Cursor *cursor;

        bool success;

        //Init Engine
        bool init();

        //Init Texture
        bool initTexture();

        //Init font
        bool initFont();

        //Init Sound
        bool initSound();

        //Read save file
        void initSave();

        //Save high score to save file
        bool save();

        void exit();

    public:
        Engine();
        ~Engine();

        //Saved high score from save file
        Sint32 savedHighscore;

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
        Text scores; //Score
        Text highscores; //High score
        Text times; //Remaing time
        Text scoreText; // "score" text
        Text highscoreText; //"high score" text
        Text timeText; // "time" text
        Text startNotice; // "START" notice text

        //Sounds
        Sound music;
        Sound startSFX;
        Sound endSFX;
        Sound matchSFX[3];

        //Generate random number
        int getRandom();

        //Update screen
        void render();
};

#endif