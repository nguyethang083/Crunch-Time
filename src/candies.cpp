#include "candies.h"

Candy::Candy(const int &nRows, const int &nCols, int time) : GameBoard(nRows, nCols, time) {
    selected = pressed = hint = false;
    highscore = engine.savedHighscore;
}

void Candy::randomize() {
    //Create board
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            board[i][j] = rand() % (Total - 1) + 1;
        }
    }
    int temp = highscore;
    while(existMatch()) {
        clear();
        refill();
    }
    highscore = temp;
    score = 0;
}

void Candy::renderCandy() {
    renderBoard();
    for(int x = 0; x < nRows; x++) {
        for(int y = 0; y < nCols; y++) {
            int COLOR = board[x][y];
            engine.candyTexture[COLOR].renderRect(&square[x][y]);
        }
    }
}

void Candy::updateCandy() {   
    renderCandy();
    engine.render();
}

bool Candy::match3(const int &row, const int &col, const std::string &direction) {
    int stepX, stepY;
    if(direction == "HORIZONTAL") {
        stepX = 0, stepY = 1;
    }
    else if(direction == "VERTICAL") {
        stepX = 1, stepY = 0;
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
                hintX = x; hintY = y; hintX_ = x+1; hintY_ = y;
                board = tempBoard;
                pendingRemoval = tempPending;
                return true;
            }
            else board = tempBoard;

            //Vertical check
            std::swap(board[x][y], board[x][y+1]);
            if(existMatch()) {
                //Set hint position
                hintX = x; hintY = y; hintX_ = x; hintY_ = y+1;
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
    engine.hintTexture.renderRect(&square[hintX][hintY]);
    engine.hintTexture.renderRect(&square[hintX_][hintY_]);
}

void Candy::renderSelector(int selectedX, int selectedY, int x, int y) {
    renderCandy();
    if(hint) {
        displayHint();
    }
    if(selected) {
        engine.selectorTexture.renderRect(&square[selectedX][selectedY]);
    }
    if(pressed) {
        engine.selectorTexture.renderRect(&square[x][y]);
    }
    engine.render();
}