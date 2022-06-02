//
// Created by JustNik on 3 Apr 2022.
//
#pragma once

#include <SDL.h>
#include <vector>
#include <memory>
#include "TextureManager.h"
#include "ecs/systems/System.h"
#include "ecs/EntityHelper.h"

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
    void initGame();
    void initSystems();
    void loop();
    void processInput();
    void render();
    void loadResources();

    GameState currentState;
    EntityHelper *entityHelper;
    SDL_Renderer *renderer;
    SDL_Window *window;
    std::vector<std::shared_ptr<System>> systems;
};