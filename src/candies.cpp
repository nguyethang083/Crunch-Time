#include "candies.h"

Candy::Candy(const int& nRows, const int& nCols) : GameBoard(nRows, nCols) {
    selected = pressed = false;
}

void Candy::randomize() {
    //Create board
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            board[i][j] = rand() % (Total - 1) + 1;
        }
    }
    while(existMatch()) {
        clear();
        refill();
    }
}

void Candy::renderCandy() {
    engine.boardTexture.render(NULL);
    for(int x = 0; x < nRows; x++) {
        for(int y = 0; y < nCols; y++) {
            int COLOR = board[x][y];
            engine.candyTexture[COLOR].render(&square[x][y]);
        }
    }
}

void Candy::updateCandy() {   
    renderCandy();
    engine.render();
}

bool Candy::match3(const int& row, const int& col, const std::string& direction) {
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
        pendingRemoval[row + i*stepX][col + i*stepY] = 1;
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

void Candy::renderSelector(int selectedX, int selectedY, int x, int y) {
    renderCandy();
    if(selected){
        engine.selectorTexture.render(&square[selectedX][selectedY]);
    }
    if(pressed) {
        engine.selectorTexture.render(&square[x][y]);
    }
    engine.render();
}