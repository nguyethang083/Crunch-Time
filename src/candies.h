#ifndef CANDIES_H
#define CANDIES_H
#include "gameboard.h"

class Candy : protected GameBoard {
    protected:
        //Candy textures
        SDL_Texture* candyTexture[Total];

        //Squares that hold candy
        vector<vector<SDL_Rect>> square;

        //Render Candies
        void renderCandy();

        //Update candies state
        void updateCandy();

    public:
        Candy(const int rows, const int cols);
        ~Candy();
};

#endif