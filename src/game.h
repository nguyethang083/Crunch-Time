#ifndef GAME_H
#define GAME_H
#include "candies.h"

class Game : private Candy {
    private:
        SDL_Event e;
        SDL_Texture* selector;
        void renderSelector();
        void swapCandies();
        void loop();
        void updateGame();

        //Coordinate
        int x, y;

        //Selected coordinate
        int selectedX, selectedY;

        //Check if key was pressed
        bool pressed;

        //Check if application is running
        bool running;

        //Check if a candy was selected
        bool selected;

    public:
        Game(const int rows, const int cols);
        ~Game();

};

#endif