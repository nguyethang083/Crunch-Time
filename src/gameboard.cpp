#include "gameboard.h"

GameBoard::GameBoard(const int &nRows, const int &nCols, int time) : nRows(nRows), nCols(nCols), time(time * 1000) {
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
    scoreBoard.y = 200;
    scoreBoard.w = 192;
    scoreBoard.h = 43;

    //Initialize highscore board
    highscoreBoard.x = 15;
    highscoreBoard.y = 100;
    highscoreBoard.w = 192;
    highscoreBoard.h = 43;

    //Initialize time board
    timeBoard.x = 15;
    timeBoard.y = 400;
    timeBoard.w = 192;
    timeBoard.h = 71;
}

void GameBoard::scoreCalculate() {
    int count = 0;
    for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nCols; col++) {
            if(pendingRemoval[row][col])
                count++;
        }
    }
    score += (count / 3) * 750 + (count % 3) * (engine.getRandom() * 10 + 300);
}

void GameBoard::clear() {
    if(!randomized)
        scoreCalculate();
    highscore = score > highscore ? score : highscore;
    
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
                board[row][col] = engine.getRandom();
            }
        }
    }
}

void GameBoard::renderStart() {
    engine.startTexture.renderTexture();
    engine.render();
}

void GameBoard::renderEnd() {
    engine.endTexture.renderTexture();
    engine.scores.renderText(400, 340);
    score = 0;
    engine.render();
}

void GameBoard::renderBoard() {
    engine.boardTexture.renderTexture();
    renderScore();
    renderHighScore();
    renderTimer();
}

void GameBoard::renderScore() {
    engine.scoreTexture.renderTexture(&scoreBoard);
    engine.scoreText.renderText(70, 170);
    engine.scores.loadText(std::to_string(score));
    engine.scores.renderText(25, -1, &scoreBoard);
}

void GameBoard::renderHighScore() {
    engine.scoreTexture.renderTexture(&highscoreBoard);
    engine.highscoreText.renderText(50, 70);
    engine.highscores.loadText(std::to_string(highscore));
    engine.highscores.renderText(25, -1, &highscoreBoard);
}

void GameBoard::renderTimer() {
    std::string minutes, seconds;
    if(gameStarted) {
        if(!gameover && !engine.timer.countdown(time)) {
            engine.timer.stop();
            gameover = true;
        }
        minutes = std::to_string(engine.timer.time / 60);
        seconds = std::to_string(engine.timer.time % 60);
    }
    else  {
        minutes = std::to_string((time/1000) / 60);
        seconds = std::to_string((time/1000) % 60);
    }

    if(std::stoi(minutes) < 10) {
        minutes = "0" + minutes;
    }
    if(std::stoi(seconds) < 10) {
        seconds = "0" + seconds;
    }

    engine.timerTexture.renderTexture(&timeBoard);
    engine.timeText.renderText(85, 370);
    engine.times.loadText(minutes + ":" + seconds);
    engine.times.renderText(-1, -1, &timeBoard);
}

void GameBoard::startNotice() {
    renderBoard();
    engine.startNotice.renderText(-1, -1);
    engine.render();
}


