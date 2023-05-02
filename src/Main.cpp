#include "game.h"
#define VERSION 2.3

/* v2.3 changelog:
    - Add hint which automatically displays hint after x seconds
    - Add additional game over condition based on hint
    - Move some variables to global
    - Modify score calculation
*/

int main(int argc, char* args[]) {
    Game game(8, 8, 120);
    return 0;
}