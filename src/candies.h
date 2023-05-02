#ifndef CANDIES_H
#define CANDIES_H
#include "gameboard.h"

class Candy : private GameBoard {
    private:
        friend class Game;

        Candy(const int &nRows, const int &nCols, int time);

        //Render Candies
        void renderCandy();

        //Update candies state
        void updateCandy();

        //Randomize candies
        void randomize();

        //Check if 3 candies are matching
        bool match3(const int &row, const int &col, const std::string &direction);

        //Check if exists at least 3 candies matched
        bool existMatch();

        //Hint handle
        bool existHint(); //Check if exist candies that can be matched
        int hintX, hintY, hintX_, hintY_; //Hint position
        bool hint; //Check if hint is needed
        void displayHint(); //Display hint

        //Draw selector
        void renderSelector(int selectedX, int selectedY, int x, int y);
};

#endif