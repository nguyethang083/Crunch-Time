#include "candies.h"

Candy::Candy(const int rows, const int cols) : GameBoard(rows, cols) {
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
    //Initialize texture
    candyTexture[Destroyed] = NULL;
    candyTexture[Red] = IMG_LoadTexture(renderer, "assets/red.jpg");
    candyTexture[Green] = IMG_LoadTexture(renderer, "assets/green.jpg");
    candyTexture[Blue] = IMG_LoadTexture(renderer, "assets/blue.jpg");
    candyTexture[Orange] = IMG_LoadTexture(renderer, "assets/orange.jpg");
    candyTexture[Pink] = IMG_LoadTexture(renderer, "assets/pink.jpg");
    for(int i = 1; i < Total; i++){
        if(candyTexture[i] == NULL){
            LogIMG("IMG_Load");
        }
    }
}

Candy::~Candy()
{
    for(int i = 0; i < Total; i++){
        SDL_DestroyTexture(candyTexture[i]);
        candyTexture[i] = NULL;
    }
}

void Candy::renderCandy()
{
    updateBoard();
    for(int x = 0; x < nRows; x++) {
        for(int y = 0; y < nCols; y++) {
            int COLOR = board[x][y];
            SDL_RenderCopy(renderer, candyTexture[COLOR], NULL, &square[x][y]);
        }
    }
}

void Candy::updateCandy()
{   
    renderCandy();
    SDL_RenderPresent(renderer);
}