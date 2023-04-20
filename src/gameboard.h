#ifndef GAME_BOARD_H
#define GAME_BOARD_H
#include <vector>
#include <string>

using namespace std;

class GameBoard {
    public: 
        vector<vector<int>> board;
        //Init board
        GameBoard(const int rows, const int cols);

        void randomize();

        //Display board
        void display();

        //Clear matching candies
        void clear();

        //Refill candies
        void refill();

        //Check if 3 candies are matched
        bool match3(int row, int col, const string& direction);

        //Check if exits at least 3 candies matching
        bool existMatch();

    private:
        const int nRows, nCols;
        vector<vector<bool>> pendingRemoval;
};

#endif