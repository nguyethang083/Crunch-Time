#include "game.h"

void Game()
{   
    srand(time(0));
    GameBoard Board(8, 8);
    Board.randomize();
    Board.display();

    int x1, y1, x2, y2;
    int count = 0;
    bool running = true;
    while(running) {
        cout << "Select first square: ";
        cin >> x1 >> y1;
        cout << "Select second square: ";
        cin >> x2 >> y2;
        swap(Board.board[x1][y1], Board.board[x2][y2]);

        if(!Board.existMatch()) {
            swap(Board.board[x1][y1], Board.board[x2][y2]);
            cout << "Invalid move!\n";
        }
        else{
            while(Board.existMatch()) {
                Board.clear();
                Board.refill();
                Board.display();
            }
        }

        count++;
        if(count == 10) {
            running = false;
        }
    }
}