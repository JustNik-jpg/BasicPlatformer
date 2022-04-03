#include <iostream>
#include <SDL.h>
#include "core/headers/Game.h"

int main(int argc, char* args[]) {
    std::cout << "Let's start!" << std::endl;

    Game game;
    game.run();

    bool running = true;

    while (running){
        game.loop();
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            default:
                break;
        }
    }

    return 0;
}
