#include "gameboard.h"

GameBoard::GameBoard(const int& nRows, const int& nCols) : nRows(nRows), nCols(nCols) {
    //Init score
    score = 0;
    
    //Init board
    board.resize(nRows, vector<int>(nCols));  

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

    //Initialize score board
    scoreBoard.x = 15;
    scoreBoard.y = 100;
    scoreBoard.w = 192;
    scoreBoard.h = 50;

    //Initialize time board
    timeBoard.x = 15;
    timeBoard.y = 400;
    timeBoard.w = 192;
    timeBoard.h = 71;

    engine.gFont[0].loadText("score");
    engine.gFont[1].loadText("time");

    //Timer time
    time = 120;
    engine.timer.start();
}

int GameBoard::scoreCalculate() {
    int count = 0;
    for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nCols; col++) {
            if(pendingRemoval[row][col])
                count++;
        }
    }
    return (count / 3) * 100 + (count % 3) * (rand() % 10 + 30);
}

void GameBoard::clear() {
    score += scoreCalculate();
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
                    std::swap(board[row][col], board[_row][col]);
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

void GameBoard::renderBoard(int score) {
    engine.boardTexture.render(NULL);
    renderScore(score);
    renderTimer();
}

void GameBoard::renderScore(int score) {
    engine.scoreTexture.render(&scoreBoard);
    engine.gFont[0].renderNew(70, 50);
    engine.scoreFont.loadText(std::to_string(score));
    engine.scoreFont.renderNew(25, 105);
}

void GameBoard::renderTimer() {
    int time_left = time - engine.timer.getTicks();
    std::string minutes = std::to_string(time_left / 60);
    std::string seconds = std::to_string(time_left % 60);

    if(std::stoi(minutes) < 10) {
        minutes = "0" + minutes;
    }
    if(std::stoi(seconds) < 10) {
        seconds = "0" + seconds;
    }

    engine.timerTexture.render(&timeBoard);
    engine.gFont[1].renderNew(70, 350);
    engine.timerFont.loadText(minutes + ":" + seconds);
    engine.timerFont.renderNew(40, 405);
}


