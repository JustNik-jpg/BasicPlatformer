//
// Created by JustNik on 3 Apr 2022.
//

#include "Game.h"
#include "iostream"
#include "ecs/ECS.h"
#include "ecs/systems/MovementSystem.h"
#include "ecs/systems/RenderSystem.h"
#include "ecs/components/Component.h"
#include <cmath>
#include "events/EventController.h"
#include "events/handlers/PlayerControlHandler.h"

ECS ecs;
EventController eventController;
Entity player;

Game::Game() {
    ecs = ECS();
}

Game::~Game() {
    delete entityHelper;
}


void Game::initGame() {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized SDL successfully";
    } else {
        std::cout << "Something went wrong when initializing SDL... " << "\n" << &SDL_GetErrorMsg;
    }
    window = SDL_CreateWindow("Basic gameussy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);

    if (!window) {
        std::cout << "Something went wrong creating the window... " << "\n" << &SDL_GetErrorMsg;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cout << "Something went wrong creating the renderer... " << "\n" << &SDL_GetErrorMsg;
    }
    ecs.init();
    initSystems();
    entityHelper = new EntityHelper(&ecs, renderer);
}


void Game::run() {
    initGame();
    currentState = GameState::ACTIVE;

    player = entityHelper->createPlayer();
    eventController.addEventHandler(new PlayerControlHandler(player));

    loop();
}

void Game::loop() {

    //Uint32 lastUpdate = 0;

    while (currentState == GameState::ACTIVE) {
        processInput();
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderClear(renderer);
        for (const auto &system: systems) {
            system->update();
        }

        Uint64 start = SDL_GetPerformanceCounter();

        //TODO convert to normal looking phys based movement system
        //Uint32 current = SDL_GetTicks();
        //float dT = (current - lastUpdate) / 256.0f;
        //lastUpdate = current;

        Uint64 end = SDL_GetPerformanceCounter();

        float elapsedMS = (end - start) / (float) SDL_GetPerformanceFrequency() * 1000.0f;
        render();

        // Cap to 60 FPS
        SDL_Delay(std::floor(16.666f - elapsedMS));
    }
}

void Game::processInput() {
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt)) {
        eventController.processEvents(evnt);
        if (evnt.type == SDL_QUIT) {
            currentState = GameState::EXIT;
        }
    }
}

void Game::render() {
    SDL_RenderPresent(renderer);
}

void Game::initSystems() {
    systems.emplace_back(ecs.registerSystem<MovementSystem>());
    auto rs = ecs.registerSystem<RenderSystem>();
    systems.emplace_back(rs);
    rs->setRenderer(renderer);

    Archetype movementArchetype;
    movementArchetype.set(ecs.getComponentID<TransformComponent>());
    ecs.setSystemArchetype<MovementSystem>(movementArchetype);

    Archetype renderArchetype;
    renderArchetype.set(ecs.getComponentID<TransformComponent>());
    renderArchetype.set(ecs.getComponentID<RenderComponent>());
    ecs.setSystemArchetype<RenderSystem>(renderArchetype);
}
