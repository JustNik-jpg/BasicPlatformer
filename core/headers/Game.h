//
// Created by JustNik on 3 Apr 2022.
//

#include <SDL.h>

enum class GameState {
    ACTIVE,
    EXIT
};

class Game {

public:
    Game();
    ~Game();
    void run();

private:
    void initSystem();
    void loop();
    void processInput();
    void render();

    GameState currentState;
    SDL_Renderer *renderer;
    SDL_Window *window;
};