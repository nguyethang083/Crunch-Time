#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include "engine.h"
#include <vector>

using namespace std;

class GameBoard : public Engine {
    public: 
        //n*n board
        vector<vector<int>> board;
        SDL_Texture* boardTexture;

        void randomize();

        //Render board
        void updateBoard();

        //Clear matching candies
        void clear();

        //Refill candies
        void refill();

        //Check if 3 candies are matched
        bool match3(int row, int col, const string& direction);

        //Check if exits at least 3 candies matching
        bool existMatch();

    public: 
        GameBoard(const int rows, const int cols);
        ~GameBoard();

    protected:
        const int nRows, nCols;
        //Candies to be removed
        vector<vector<bool>> pendingRemoval;
};

#endif