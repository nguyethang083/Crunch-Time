#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include "engine.h"
#include <vector>

using namespace std;

class GameBoard : protected Engine {
    private:
        //Board Texture
        SDL_Texture* boardTexture;

    protected:
        //Board size
        const int nRows, nCols;

        //n*n board
        vector<vector<int>> board;

        //Squares that hold candy
        vector<vector<SDL_Rect>> square;

       //Candies to be removed
       vector<vector<bool>> pendingRemoval;

       GameBoard(const int& rows, const int& cols);
        ~GameBoard();

        //Render board
        void updateBoard();

        //Clear matching candies
        void clear();

        //Refill candies
        void refill();

};

#endif