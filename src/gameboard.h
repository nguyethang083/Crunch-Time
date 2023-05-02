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

        bool gameover;

        GameBoard(const int &nRows, const int &nCols, int time);
        
        //Game start screen
        void renderStart();
        //Game end screen
        void renderEnd();

        //Render game boards
        void renderBoard(int score);

        //Render timer;
        SDL_Rect timeBoard;
        Uint32 time;
        void renderTimer();

        //Render score
        SDL_Rect scoreBoard;
        void renderScore(int score);
        int score;
        int scoreCalculate();

        //Clear matching candies
        void clear();

        //Refill candies
        void refill();

};

#endif