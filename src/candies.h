#ifndef CANDIES_H
#define CANDIES_H
#include "gameboard.h"

class Candy : private GameBoard {
    private:
        friend class Game;

        Candy(const int &nRows, const int &nCols);

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
        bool needHint; //Check if hint is needed
        void displayHint(); //Display hint
        Timer hint; //Hint timer

        //Draw selector
        void renderSelector(const int &selectedX, const int &selectedY, const int &x, const int &y);

        //Update game state
        void updateGame();

        //Save game state
        void saveState();
};

#endif