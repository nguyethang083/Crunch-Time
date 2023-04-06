#include <bits/stdc++.h>
using namespace std;

const int row = 8;
const int col = 8;

//Initialize 8x8 board
int board[row][col];
int pendingRemoval[row][col];

enum Jewels{Destroyed, Red, Green, Blue, Orange, White, Total};

//Display board
void display();

//Check match
bool matched(int x, int y, int stepX, int stepY);
bool existsMatch(){
    bool exist = false;
    //Horizontal match
    for(int x = 0; x < row; x++){
        for(int y = 0; y < col - 2; y++){
            if(matched(x, y, 0, 1)){
                exist = true;
            }
        }
    }
    //Vertical match
    for(int x = 0; x < row - 2; x++){
        for(int y = 0; y < col; y++){
            if(matched(x, y, 1, 0)){
                exist = true;
            }
        }    
    }
    return exist;
}

//Remove matching candies
void remove();

//Fill destroyed candy
void fill();

int main(){
    srand(time(0));
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            board[i][j] = rand() % (Total-1) + 1;
        }
    }
    while(existsMatch()){
        remove();
        fill();
    }
    display();
    bool running = true;
    int x1, y1, x2, y2;
    while(running){
        cout << "Select first square: ";
        cin >> x1 >> y1;
        cout << "Select second square: ";
        cin >> x2 >> y2;
        swap(board[x1][y1], board[x2][y2]);
        if(!existsMatch()){
            swap(board[x1][y1], board[x2][y2]);
            cout << "Invalid move!\n";
        }
        else{
            while(existsMatch()){
                remove();
                display();
                fill();
                display();
            }
        }
    }
}

void display()
{
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            switch(board[row][col]){
                case Red:
                    cout << "\x1B[31m";
                    break;
                case Green:
                    cout << "\x1B[32m";
                    break;
                case Blue:
                    cout << "\x1B[34m";;
                    break;
                case Orange:
                    cout << "\x1B[33m";;
                    break;
                case White:
                    cout << "\x1B[37m";
                    break;
            }
            cout << board[row][col] << ' ';
        }
        cout << '\n';
    }
    cout << setfill('_') << setw(15) << '_' << "\033[0m\n\n";
};

bool matched(int x, int y, int stepX, int stepY){
    //Starting value
    const int start = board[x][y];
    for(int i = 1; i < 3; i++){
        if(board[x + i*stepX][y + i*stepY] != start){
            return false;
        }
    }
    for(int i = 0; i < 3; i++){
        pendingRemoval[x + i*stepX][y + i*stepY] = 1;
    }
    return true;
}

void remove(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(pendingRemoval[i][j] == 1){
                board[i][j] = Destroyed;
            }
        }
    }
    memset(pendingRemoval, 0, sizeof(pendingRemoval));
}

void fill(){
    //Drop candies down
    for(int j = 0; j < col; j++){
        for(int i = row - 1; i >=0; i--){
            for(int k = i - 1; k >= 0; k--){
                if(board[i][j] == Destroyed && board[k][j] != 0){
                    swap(board[i][j], board[k][j]);
                }
            }
        }
    }
    //Fill empty squares with new candies
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            if(board[i][j] == Destroyed){
                board[i][j] = rand() % (Total-1) + 1;
            }
        }
    }
}
