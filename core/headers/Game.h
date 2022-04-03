//
// Created by JustNik on 3 Apr 2022.
//

#include <SDL.h>


class Game {

public:
    Game();
    ~Game();
    void run();
    void loop();

private:
    void initSystem();
    SDL_Window *window;
};