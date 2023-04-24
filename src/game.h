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

        int x,y, selectedX, selectedY;
        bool pressed, running, selected;

    public:
        Game(const int rows, const int cols);
        ~Game();

};

#endif