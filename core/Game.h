//
// Created by JustNik on 3 Apr 2022.
//
#pragma once

#include <SDL.h>
#include "entity/ECS.h"
#include "TextureManager.h"

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
    void loadResources();

    GameState currentState;
    SDL_Renderer *renderer;
    SDL_Window *window;
    Manager entityManager;
    Entity *player;
};