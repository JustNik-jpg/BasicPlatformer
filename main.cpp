#include <iostream>
#include <SDL.h>
#include "core/Game.h"

int main(int argc, char* args[]) {
    std::cout << "Let's start!" << std::endl;

    Game game;
    game.run();

    return 0;
}
