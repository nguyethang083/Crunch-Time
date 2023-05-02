#ifndef GAME_H
#define GAME_H
#include "candies.h"

class Game {
    private:
        SDL_Event e;
        SDL_TimerID timerID;

        //Mouse postion
        SDL_Point pos;

        //Delay function
        Timer delay;

        Candy candy;

        int nRows, nCols;

        //Coordinate
        int x, y;

        //Selected coordinate
        int selectedX, selectedY;

        //Keyboard event
        void keyControl();
        //Mouse event
        void mouseControl();

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
        bool gameEnded;

        //Check if game is running
        bool running;

        static Uint32 callback(Uint32 interval, void* param);
    
    public:
        Game(const int &nRows, const int &nCols, int time);

};

#endif