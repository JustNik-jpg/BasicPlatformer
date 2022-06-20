//
// Created by JustNik on 3 Apr 2022.
//

#include "Game.h"
#include "iostream"
#include "ecs/systems/MovementSystem.h"
#include "ecs/systems/RenderSystem.h"
#include "ecs/components/Component.h"
#include <cmath>
#include "events/handlers/PlayerControlHandler.h"
#include "Engine.h"

Engine engine;

Game::Game() {
}

Game::~Game() {

}


void Game::initGame() {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized SDL successfully";
    } else {
        std::cout << "Something went wrong when initializing SDL..." << "\n" << &SDL_GetErrorMsg;
    }
    engine.window = SDL_CreateWindow("Basic gameussy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);

    if (!engine.window) {
        std::cout << "Something went wrong creating the window... " << "\n" << &SDL_GetErrorMsg;
    }

    engine.renderer = SDL_CreateRenderer(engine.window, -1, 0);
    if (!engine.renderer) {
        std::cout << "Something went wrong creating the renderer... " << "\n" << &SDL_GetErrorMsg;
    }
    engine.ecs = new ECS();
    engine.eventController = new EventController();
    engine.ecs->init();
    initSystems();
    engine.entityHelper = new EntityHelper(engine.ecs, engine.renderer);
}


void Game::run() {
    initGame();
    currentState = GameState::ACTIVE;

    Entity player = engine.entityHelper->createPlayer();
    engine.eventController->addEventHandler(new PlayerControlHandler(player));

    loop();
}

void Game::loop() {

    //Uint32 lastUpdate = 0;

    while (currentState == GameState::ACTIVE) {
        processInput();
        SDL_SetRenderDrawColor(engine.renderer, 0, 255, 0, 255);
        SDL_RenderClear(engine.renderer);
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
        engine.eventController->processEvents(evnt);
        if (evnt.type == SDL_QUIT) {
            currentState = GameState::EXIT;
        }
    }
}

void Game::render() {
    SDL_RenderPresent(engine.renderer);
}

void Game::initSystems() {
    systems.emplace_back(engine.ecs->registerSystem<MovementSystem>());
    systems.emplace_back(engine.ecs->registerSystem<RenderSystem>());

    Archetype movementArchetype;
    movementArchetype.set(engine.ecs->getComponentID<TransformComponent>());
    engine.ecs->setSystemArchetype<MovementSystem>(movementArchetype);

    Archetype renderArchetype;
    renderArchetype.set(engine.ecs->getComponentID<TransformComponent>());
    renderArchetype.set(engine.ecs->getComponentID<RenderComponent>());
    engine.ecs->setSystemArchetype<RenderSystem>(renderArchetype);
}
