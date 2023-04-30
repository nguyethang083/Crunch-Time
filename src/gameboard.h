#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include "engine.h"
#include <vector>
using std::vector; 

class GameBoard {
    protected:
        Engine engine;

        //Board size
        const int nRows, nCols;

        //n*n board
        vector<vector<int>> board;

        //Squares that hold candy
        vector<vector<SDL_Rect>> square;

       //Candies to be removed
        vector<vector<bool>> pendingRemoval;

        SDL_Rect scoreBoard;

        GameBoard(const int& nRows, const int& nCols);

        //Render game boards
        void renderBoard(int score);

        //Clear matching candies
        void clear();

        //Refill candies
        void refill();

        int score;
        int scoreCalculate();

};

#endif