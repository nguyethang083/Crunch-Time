#ifndef CANDIES_H
#define CANDIES_H
#include "gameboard.h"

class Candy : protected GameBoard {
    private:
        //Candy textures
        SDL_Texture* candyTexture[Total];
        friend class Game;

        Candy(const int& rows, const int& cols);
        ~Candy();

        //Render Candies
        void renderCandy();

        //Update candies state
        void updateCandy();

        //Randomize candies
        void randomize();

        //Check if 3 candies are matching
        bool match3(const int& row, const int& col, const std::string& direction);

        //Check if exists at least 3 candies matched
        bool existMatch();
};

#endif