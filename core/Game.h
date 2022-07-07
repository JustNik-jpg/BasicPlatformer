//
// Created by JustNik on 3 Apr 2022.
//
#pragma once

#include <SDL.h>
#include <vector>
#include <memory>
#include "TextureHelper.h"
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

    GameState currentState;
    std::vector<std::shared_ptr<System>> systems;
};