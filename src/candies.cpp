#include "Candies.h"

Candy::Candy(const int &nRows, const int &nCols) : GameBoard(nRows, nCols) {
    selected = pressed = needHint = false;
}

void Candy::randomize() {
    if(forceQuit && selectChange == ContinueSelection) {
        score = engine.savedScore;
        board = engine.savedBoard;
        time = engine.savedTime;
        forceQuit = false;
    } else {
        randomized = true;
        //Board creation
        for(int i = 0; i < nRows; i++) {
            for(int j = 0; j < nCols; j++) {
                board[i][j] = engine.getRandom();
            }
        }
        while(existMatch()) {
            clear();
            refill();
        }
        randomized = false;
    }
}

void Candy::renderCandy() {
    renderBoard();
    for(int x = 0; x < nRows; x++) {
        for(int y = 0; y < nCols; y++) {
            int COLOR = board[x][y];
            engine.candyTexture[COLOR].renderTexture(&square[x][y]);
        }
    }
}

void Candy::updateCandy() {   
    renderCandy();
}

bool Candy::match3(const int &row, const int &col, const std::string &direction) {
    int stepX = 0;
    int stepY = 0;
    if(direction == "HORIZONTAL") {
        stepY = 1;
    } else if(direction == "VERTICAL") {
        stepX = 1;
    }

    //Starting value
    const int start = board[row][col];
    for(int i = 1; i < 3; i++) {
        if(board[row + i*stepX][col + i*stepY] != start) {
            return false;
        }
    }

    //Mark candies to be removed
    for(int i = 0; i < 3; i++) {
        pendingRemoval[row + i*stepX][col + i*stepY] = true;
    }
    return true;
}

bool Candy::existMatch() {
    bool exist = false;

    //Horizontal match
    for(int row = 0; row < nRows; row++) {
        for(int col = 0; col < nCols - 2; col++) {
            if(match3(row, col, "HORIZONTAL")) {
                exist = true;
            }
        }
    }

    //Vertical match
    for(int row = 0; row < nRows - 2; row++) {
        for(int col = 0; col < nCols; col++) {
            if(match3(row, col, "VERTICAL")) {
                exist = true;
            }
        }    
    }
    return exist;
}

bool Candy::existHint() {
    vector<vector<int>> tempBoard = board;
    vector<vector<bool>> tempPending = pendingRemoval;
    for(int x = 0; x < nRows - 1; x++) {
        for(int y = 0; y < nCols - 1; y++) {
            //Horizontal check
            std::swap(board[x][y], board[x+1][y]);
            if(existMatch()) {
                //Set hint position
                hintX = x; hintY = y; hintX_ = x + 1; hintY_ = y;
                board = tempBoard;
                pendingRemoval = tempPending;
                return true;
            }
            else board = tempBoard;

            //Vertical check
            std::swap(board[x][y], board[x][y+1]);
            if(existMatch()) {
                //Set hint position
                hintX = x; hintY = y; hintX_ = x; hintY_ = y + 1;
                board = tempBoard;
                pendingRemoval = tempPending;
                return true;
            }
            else board = tempBoard;
        }
    }
    return false;
}

void Candy::displayHint() {
    if(!hint.countdown(7000)) {
        needHint = true;
    }
    if(needHint) {
        engine.hintTexture.renderTexture(&square[hintX][hintY]);
        engine.hintTexture.renderTexture(&square[hintX_][hintY_]);
    }
}

void Candy::renderSelector(const int &selectedX, const int &selectedY, const int &x, const int &y) {
    renderCandy();
    displayHint();
    if(selected) {
        engine.selectorTexture.renderTexture(&square[selectedX][selectedY]);
    }
    if(pressed) {
        engine.selectorTexture.renderTexture(&square[x][y]);
    }
}

void Candy::updateGame() {
    int count = 0;
    while(existMatch()) {
        hint.stop();
        needHint = false;

        //Choose which sfx to play
        count++;
        if(count == 1) {
            engine.matchSFX[0].playSFX();
        }
        else if(count == 2) {
            engine.matchSFX[1].playSFX();
        }
        else engine.matchSFX[2].playSFX();

        //Matching actions
        clear();
        updateCandy();
        refill();
        updateCandy();
    }
}

void Candy::saveState() {
    engine.savedScore = score;
    engine.savedTime = engine.timer.time;
    engine.savedBoard = board;
}