#include "gameboard.h"

GameBoard::GameBoard(const int &nRows, const int &nCols) : nRows(nRows), nCols(nCols) {
    score = 0;

    //Initialize board
    board.resize(nRows, vector<int>(nCols));

    //Initialize squares
    square.resize(nRows, vector<SDL_Rect>(nCols));
    int startX = 240, startY = 35;
    for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nCols; col++) {
            square[row][col] = (SDL_Rect) {col * 65 + startX, row * 65 + startY, 65, 65};
        }
    }

    pendingRemoval.resize(nRows, vector<bool>(nCols));

    //Initialize score board
    scoreBoard = (SDL_Rect) {15, 200, 192, 43};
    //Initialize highscore board
    highscoreBoard = (SDL_Rect) {15, 100, 192, 43};
    //Initialize time board
    timeBoard = (SDL_Rect) {15, 400, 192, 71};
    //Initialize exit box
    exit = (SDL_Rect) {15, 500, 194, 43};

    //Inititalize select box
    continueSelect = (SDL_Rect) {325, 400, 160, 35};
    newGameSelect = (SDL_Rect) {325, 440, 160, 35};
    modeSelect = (SDL_Rect) {325, 475, 160, 30};
    timeSelect = (SDL_Rect) {340, 505, 125, 30};
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
    *highscore = score > *highscore ? score : *highscore;

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
        for(int row = nRows - 1; row >= 0; row--) {
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

void GameBoard::renderHighlight(SDL_Rect &rect) {
    engine.highlightTexture.renderTexture(&rect);
}

void GameBoard::renderStart() {
    engine.timer.stop();
    score = 0;
    engine.startTexture.renderTexture();

    if(forceQuit) {
        engine.continueText.renderText(-1, -1, &continueSelect);
    }
    engine.newGameText.renderText(-1, -1, &newGameSelect);

    if(selectChange != ContinueSelection) {
        engine.gameModeText.loadText("<" + game_mode[gameMode] + " mode>");
        engine.gameModeText.renderText(-1, -1, &modeSelect);

        if(gameMode == Time) {
            time = time_mode[timeMode];
            if(time <= 120 || time % 60 != 0)
                engine.timeModeText.loadText(std::to_string(time) + " seconds");
            else engine.timeModeText.loadText(std::to_string(time / 60) + " minutes");
            engine.timeModeText.renderText(-1, -1, &timeSelect);
        }
    }

    switch(selectChange) {
        case ContinueSelection:
            renderHighlight(continueSelect);
            break;

        case NewGameSelection:
            renderHighlight(newGameSelect);
            break;

        case GameSelection:
            renderHighlight(modeSelect);
            break;

        case TimeSelection:
            renderHighlight(timeSelect);
            break;
    }
    engine.render();
}

void GameBoard::renderEnd() {
    engine.endTexture.renderTexture();
    engine.scores.renderText(425, 340);
    engine.render();
    score = 0;
    time = time_mode[timeMode];
}

void GameBoard::renderBoard() {
    engine.boardTexture.renderTexture();
    engine.exitTexture.renderTexture(&exit);
    renderScore();
    renderHighScore();
    if(gameMode == Time)
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
    engine.highscores.loadText(std::to_string(*highscore));
    engine.highscores.renderText(25, -1, &highscoreBoard);
}

void GameBoard::renderTimer() {
    std::string minutes, seconds;
    if(gameover) {
        engine.timer.stop();
    } else if(!engine.timer.countdown(time * 1000)) {
        gameover = true;
    }
    minutes = std::to_string(engine.timer.time / 60);
    seconds = std::to_string(engine.timer.time % 60);

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
    SDL_Delay(1000);
    renderBoard();
    engine.startNotice.renderText(-1, -1);
    engine.render();
    SDL_Delay(700);
}