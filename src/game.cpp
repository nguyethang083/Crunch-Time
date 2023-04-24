#include "game.h"

Game::Game(const int rows, const int cols) : Candy(rows, cols) {
    selector = IMG_LoadTexture(renderer, "assets/selector.png");
    if(selector == NULL) {
        LogIMG("IMG_Load");
    }

    x = y = 0;
    running = true;
    selected = pressed = false;
    randomize();
    updateCandy();
    loop();
}

Game::~Game() {
    SDL_DestroyTexture(selector);
    selector = NULL;
    IMG_Quit();
    SDL_Quit();
}

void Game::renderSelector() {
    renderCandy();
    if(selected){
        SDL_RenderCopy(renderer, selector, NULL, &square[selectedX][selectedY]);
    }
    SDL_RenderCopy(renderer, selector, NULL, &square[x][y]);
    SDL_RenderPresent(renderer);
}

void Game::swapCandies() {
    switch(e.key.keysym.sym){
        case SDLK_UP:
            x--;
            if(selected) {
                y = selectedY;
                if(x < 0)
                    x = selectedX;
                if(x != selectedX)
                    x = selectedX - 1;
            }
            else if(x == -1)
                x = nRows - x - 2;
            break;
        case SDLK_DOWN:
            x++;
            if(selected) {
                y = selectedY;
                if(x < 0)
                    x = selectedX;
                if(x != selectedX)
                    x = selectedX + 1;
            }
            else if(x == nRows)
                x = 0;
            break;
        case SDLK_LEFT:
            y--;
            if(selected) {
                x = selectedX;
                if(y < 0)
                    y = selectedY;
                if(y != selectedY)
                    y = selectedY - 1;
            }
            else if(y == -1)
                y = nCols - y - 2;
            break;
        case SDLK_RIGHT:
            y++;
            if(selected) {
                x = selectedX;
                if(y < 0)
                    y = selectedY;
                if(y != selectedY)
                    y = selectedY + 1;
            }
            else if(y == nRows)
                y = 0;
            break;
        case SDLK_RETURN:
            if(!selected) {
                selectedX = x, selectedY = y;
                selected = true;
            }
            else {
                std::swap(board[selectedX][selectedY], board[x][y]);
                updateCandy();
                SDL_Delay(300);
                if(!existMatch()) {
                    swap(board[selectedX][selectedY], board[x][y]);
                    updateCandy();
                    SDL_Delay(300);
                }
                x = y = 0;
                selected = pressed = false;
            }
            break;

    }
}

void Game::updateGame() {
    while(existMatch()) {
        clear();
        updateCandy();
        SDL_Delay(500);
        refill();
        updateCandy();
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

        
    