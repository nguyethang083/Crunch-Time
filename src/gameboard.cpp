#include "gameboard.h"

GameBoard::GameBoard(const int& rows, const int& cols) : nRows(rows), nCols(cols) {
    //Init board
    board.resize(nRows, vector<int>(nCols));  

    boardTexture = IMG_LoadTexture(renderer, "assets/Background.png");
        if(boardTexture == NULL){
        LogIMG("IMG_Load");
    }

    //Initialize squares
    square.resize(nRows, vector<SDL_Rect>(nCols));
    int startX = 240, startY = 35;
    for(int row = 0; row < nRows; row++){
        for(int col = 0; col < nCols; col++){
            square[row][col].x = col * 65 + startX;
            square[row][col].y = row * 65 + startY;
            square[row][col].w = 65;
            square[row][col].h = 65;
        }
    }

    pendingRemoval.resize(nRows, vector<bool>(nCols));
}

GameBoard::~GameBoard() {
    SDL_DestroyTexture(boardTexture);
    boardTexture = NULL;
}

void GameBoard::updateBoard() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, boardTexture, NULL, NULL);
}

void GameBoard::clear() {
    for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nCols; col++) {
            if(pendingRemoval[row][col]) {
                board[row][col] = Destroyed;
                pendingRemoval[row][col] = false;
            }
        }
    }
}

void GameBoard::refill() {
    //Drop candies down
    for(int col = 0; col < nCols; col++) {
        for(int row = nRows - 1; row >=0; row--) {
            for(int _row = row - 1; _row >= 0; _row--) {
                if(board[row][col] == Destroyed && board[_row][col] != 0) {
                    swap(board[row][col], board[_row][col]);
                }
            }
        }
    }

    //Fill empty squares with new candies
    for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nCols; col++) {
            if(board[row][col] == Destroyed) {
                board[row][col] = rand() % (Total - 1) + 1;
            }
        }
    }

}

