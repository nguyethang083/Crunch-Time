#include "game.h"

Game::Game(const int& rows, const int& cols) : candy(rows, cols) {
    x = y = 0;
    running = true;
    selected = pressed = false;
    
    //Init selector
    selector = IMG_LoadTexture(candy.renderer, "assets/selector.png");
    if(selector == NULL) {
        LogIMG("IMG_Load");
    }

    candy.randomize();
    candy.updateCandy();
    loop();
}

Game::~Game() {
    SDL_DestroyTexture(selector);
    selector = NULL;
    IMG_Quit();
    SDL_Quit();
}

void Game::renderSelector() {
    candy.renderCandy();
    if(selected){
        SDL_RenderCopy(candy.renderer, selector, NULL, &candy.square[selectedX][selectedY]);
    }
    if(pressed) {
        SDL_RenderCopy(candy.renderer, selector, NULL, &candy.square[x][y]);
    }
    
    SDL_RenderPresent(candy.renderer);
}

void Game::swapCandies() {
    switch(e.key.keysym.sym){
        case SDLK_UP: case SDLK_w:
            x--;
            if(selected) {
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
            if(selected) {
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
            if(selected) {
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
            if(selected) {
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
            if(!selected) {
                selectedX = x, selectedY = y;
                selected = true;
            }
            else {
                if(x != selectedX || y != selectedY) {
                    swap(candy.board[selectedX][selectedY], candy.board[x][y]);
                    candy.updateCandy();
                    SDL_Delay(300);
                    if(!candy.existMatch()) {
                        swap(candy.board[selectedX][selectedY], candy.board[x][y]);
                        candy.updateCandy();
                        SDL_Delay(300);
                    }
                    x = y = 0;
                    pressed = false;
                }
                else {
                    x = selectedX;
                    y = selectedY;
                    pressed = true;
                }
                selected = false;
            }
            break;

    }
}

void Game::updateGame() {
    while(candy.existMatch()) {
        candy.clear();
        candy.updateCandy();
        SDL_Delay(400);
        candy.refill();
        candy.updateCandy();
    }
}

void Game::loop() {
    while(running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        if(e.type == SDL_KEYDOWN) {
            if(!pressed){
                pressed = true;
            } else swapCandies();
            renderSelector();
            updateGame();
        }
    }
}

        
    