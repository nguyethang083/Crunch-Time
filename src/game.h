#ifndef GAME_H
#define GAME_H
#include "candies.h"

class Game {
    private:
        SDL_Event e;

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

        //Check if application is running
        bool running;

    public:
        Game(const int& nRows, const int& nCols);

};

#endif