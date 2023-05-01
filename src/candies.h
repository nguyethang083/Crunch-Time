#ifndef CANDIES_H
#define CANDIES_H
#include "gameboard.h"

class Candy : private GameBoard {
    private:
        friend class Game;

        Candy(const int& nRows, const int& nCols, int time);

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

        //Check if a candy was selected
        bool pressed, selected;

        //Draw selector
        void renderSelector(int selectedX, int selectedY, int x, int y);
};

#endif