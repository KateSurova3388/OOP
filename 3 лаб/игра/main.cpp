#include <iostream>
#include "Game.h"
int main() {
    std::vector<int> ships = {4,3,2};
    Game* game = new Game(10,5,ships);
    game->play();
    delete game;


}
