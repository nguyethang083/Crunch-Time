#ifndef GAME_H
#define GAME_H
#include "candies.h"

class Game {
    private:
        SDL_Event e;

        //Selector texture
        SDL_Texture* selector;

        //Draw selector
        void renderSelector();

        Candy candy;

        //Coordinate
        int x, y;

        //Selected coordinate
        int selectedX, selectedY;

        //Swap 2 candies
        void swapCandies();

        void loop();
        void updateGame();


        //Check if key was pressed
        bool pressed;

        //Check if application is running
        bool running;

        //Check if a candy was selected
        bool selected;

    public:
        Game(const int& rows, const int& cols);
        ~Game();

};

#endif