#include "game.h"

Game::Game(const int& nRows, const int& nCols) : candy(nRows, nCols) {
    gameStarted = false;
    running = true;

    startGame();
    candy.randomize();
    candy.updateCandy();

    x = y = 0;
    loop();
}

void Game::startGame() {
    while(!gameStarted && running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        else {
            candy.renderStart();
            if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_RETURN)
                    gameStarted = true;
            }
        }
    }
}

void Game::endGame() {
    candy.renderEnd();
    if(e.type == SDL_KEYDOWN) {
        if(e.key.keysym.sym == SDLK_RETURN) {
            candy.randomize();
            candy.gameOver = false;
            timerID = SDL_AddTimer(1000, callback, NULL);
            while(delay.countdown(750));
        }
    }
}

void Game::updateGame() {
     while(candy.existMatch()) {
        candy.clear();
        candy.updateCandy();
        while(delay.countdown(500));
        candy.refill();
        candy.updateCandy();
    }
}

Uint32 Game::callback(Uint32 interval, void* param) {
    SDL_Event event;
    SDL_UserEvent userevent;

    userevent.type = SDL_USEREVENT;
    userevent.code = 0;
    userevent.data1 = NULL;
    userevent.data2 = NULL;

    event.type = SDL_USEREVENT;
    event.user = userevent;

    SDL_PushEvent(&event);
    return(interval);
}

void Game::loop() {
    timerID = SDL_AddTimer(1000, callback, NULL);
    while(running && SDL_WaitEvent(&e)) {
        if(e.type == SDL_QUIT)
            running = false;
        if(candy.gameOver) {
            SDL_RemoveTimer(timerID);
            endGame();
        }
        else {
            if(e.type == SDL_KEYDOWN) {
                if(!candy.pressed) {
                    candy.pressed = true;
                }
                else swapCandies();
                candy.renderSelector(selectedX, selectedY, x, y);
                updateGame();
            }
                else candy.renderSelector(selectedX, selectedY, x, y);
            }
        } 
    SDL_RemoveTimer(timerID);
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
                    while(delay.countdown(300));
                    if(!candy.existMatch()) {
                        std::swap(candy.board[selectedX][selectedY], candy.board[x][y]);
                        candy.updateCandy();
                        while(delay.countdown(300));
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

        
    