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
        Timer hint;

        Candy candy;

        //Board size
        int nRows, nCols;

        //Coordinate
        int x, y;

        //Selected coordinate
        int selectedX, selectedY;

        //Keyboard handle
        void keyControl();
        
        //Mouse handle
        void mouseControl();
        bool click; //Check is mouse was clicked
        bool drag; //Check if mouse is dragging

        //Check if candies can be swapped
        bool swapCheck();
        //Swap candies
        void swapCandies();
        
        //Game loop
        void run();

        //Update game state
        void updateGame();

        //Game state
        void startGame();
        void endGame();
        
        //The actual start function
        void start();

        //Check if game is running
        bool running;

        static Uint32 callback(Uint32 interval, void* param);
    
    public:
        /**
         * Create a game board with nRows rows and nCols column
         * \param nRows number of rows
         * \param nCols number of column
         * \param time game's timer
        */
        Game(const int &nRows, const int &nCols, int time);

};

#endif