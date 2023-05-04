#ifndef ENGINE_H
#define ENGINE_H
#include "Texture.h"
#include "Text.h"
#include "Timer.h"
#include "Sound.h"
#include <vector>
using std::vector;

//Candies in squares
enum Candies {Destroyed, Red, Green, Blue, Orange, Pink, Gold, Total};

//Game modes
enum GameModes {Time, Zen, Endless, Total_Mode};

//Time modes
enum TimeModes {OneMinute, TwoMinutes, FiveMinutes, Total_Time};

//Change selection
enum SelectionChange {ContinueSelection, NewGameSelection, GameSelection, TimeSelection, Total_Selection};

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

        //Read save data
        void initSave();

        //Save high score to disk
        bool save();

        void exit();

    public:
        Engine();
        ~Engine();

        //Saved high score from disk
        Sint32 savedHighscore[Total_Mode][Total_Time];
        //Saved state
        Sint32 savedScore;
        Uint32 savedTime;
        vector<vector<int>> savedBoard;

        Timer timer; 
        
        //Textures
        Texture boardTexture; //Board texture
        Texture candyTexture[Total]; //Candies textures
        Texture selectorTexture; //Selector texture
        Texture hintTexture; // Hint texture
        Texture scoreTexture; //Score texture
        Texture timerTexture; //Timer texture
        Texture highlightTexture; //Highlight selection texture
        Texture bossTexture; //Boss texture
        Texture exitTexture; //Exit texture
        Texture startTexture; //Start screen texture
        Texture endTexture; //End screen texture

        //Texts
        Text continueText;
        Text newGameText;
        Text gameModeText; //Game modes
        Text timeModeText; //Time modes
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