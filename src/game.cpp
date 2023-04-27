#include "game.h"

Game::Game(const int& nRows, const int& nCols) : candy(nRows, nCols) {
    x = y = 0;
    running = true;

    candy.randomize();
    candy.updateCandy();
    loop();
}

void Game::updateGame() {
     while(candy.existMatch()) {
        candy.clear();
        candy.updateCandy();
        SDL_Delay(450);
        candy.refill();
        candy.updateCandy();
    }
}

void Game::loop() {
    while(running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        if(e.type == SDL_KEYDOWN) {
            if(!candy.pressed){
                candy.pressed = true;
            }
            else swapCandies();
            candy.renderSelector(selectedX, selectedY, x, y);
            updateGame();
        }
    }
    
}

void Game::swapCandies() {
    switch(e.key.keysym.sym){
        case SDLK_UP: case SDLK_w:
            x--;
            if(candy.selected) {
                y = selectedY;
                if(x < 0)
                    x = selectedX;
                if(x != selectedX)
                    x = selectedX - 1;
            }
            else if(x == -1)
                x = candy.nRows - x - 2;
            break;
        case SDLK_DOWN: case SDLK_s:
            x++;
            if(candy.selected) {
                y = selectedY;
                if(x < 0)
                    x = selectedX;
                if(x != selectedX)
                    x = selectedX + 1;
            }
            else if(x == candy.nRows)
                x = 0;
            break;
        case SDLK_LEFT: case SDLK_a:
            y--;
            if(candy.selected) {
                x = selectedX;
                if(y < 0)
                    y = selectedY;
                if(y != selectedY)
                    y = selectedY - 1;
            }
            else if(y == -1)
                y = candy.nCols - y - 2;
            break;
        case SDLK_RIGHT: case SDLK_d:
            y++;
            if(candy.selected) {
                x = selectedX;
                if(y < 0)
                    y = selectedY;
                if(y != selectedY)
                    y = selectedY + 1;
            }
            else if(y == candy.nRows)
                y = 0;
            break;
        case SDLK_RETURN: case SDLK_SPACE:
            if(!candy.selected) {
                selectedX = x, selectedY = y;
                candy.selected = true;
            }
            else {
                if(x != selectedX || y != selectedY) {
                    std::swap(candy.board[selectedX][selectedY], candy.board[x][y]);
                    candy.updateCandy();
                    SDL_Delay(300);
                    if(!candy.existMatch()) {
                        std::swap(candy.board[selectedX][selectedY], candy.board[x][y]);
                        candy.updateCandy();
                        SDL_Delay(300);
                    }
                    x = y = 0;
                    candy.pressed = false;
                }
                else {
                    x = selectedX;
                    y = selectedY;
                    candy.pressed = true;
                }
                candy.selected = false;
            }
            break;

    }
}

        
    