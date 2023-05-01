#ifndef GAME_H
#define GAME_H
#include "candies.h"

class Game {
    private:
        SDL_Event e;
        SDL_TimerID timerID;
        Timer delay;

        Candy candy;

        //Coordinate
        int x, y;

        //Selected coordinate
        int selectedX, selectedY;

        //Swap 2 candies
        void swapCandies();

        void loop();

        //Update game state
        void updateGame();

        
        //Check if game has started
        bool gameStarted;

        //Game state
        void startGame();
        void endGame();

        //Check if game is running
        bool running;

        static Uint32 callback(Uint32 interval, void* param);
    
    public:
        Game(const int& nRows, const int& nCols);

};

#endif