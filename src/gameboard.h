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

        //Return true if board was randomized
        bool randomized;

        GameBoard(const int &nRows, const int &nCols);
        
        //Game start screen
        void renderStart();
        //Game end screen
        void renderEnd();

        //Render game boards
        void renderBoard();

        //Notice game is starting
        void startNotice();

        //Highlight selection
        void renderHighlight(SDL_Rect &rect);

        //Render timer;
        SDL_Rect timeBoard;
        Uint32 time;
        void renderTimer();

        //Render score
        SDL_Rect scoreBoard;
        SDL_Rect highscoreBoard;
        void renderScore();
        void renderHighScore();
        Sint32 score;
        void scoreCalculate();

        //Mode select
        SDL_Rect modeSelect;
        SDL_Rect timeSelect;

        SDL_Rect exit;
        
        //Clear matching candies
        void clear();

        //Refill candies
        void refill();

};

#endif