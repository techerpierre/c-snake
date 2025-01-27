#include <stdio.h>
#include "Game.h"

int main(int argc, char **argv) {
    Game *game = Game_Init();
    Game_Run(game);
    game = Game_Quit(game);
    return 0;
}