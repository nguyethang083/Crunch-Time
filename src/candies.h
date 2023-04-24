#ifndef CANDIES_H
#define CANDIES_H
#include "gameboard.h"

class Candy : protected GameBoard {
    protected:
        //Candy textures
        SDL_Texture* candyTexture[Total];
        //Squares that hold candy
        vector<vector<SDL_Rect>> square;
    
    public: 
        Candy(const int rows, const int cols);
        ~Candy();

        //Render Candies
        void renderCandy();
        void updateCandy();
};

#endif