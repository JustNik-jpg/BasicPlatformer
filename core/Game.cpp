//
// Created by JustNik on 3 Apr 2022.
//

#include "Game.h"
#include "iostream"
#include "ecs/ECS.h"
#include "ecs/systems/MovementSystem.h"
#include "ecs/components/Component.h"
#include <cmath>

ECS ecs;
Entity player;

Game::Game() {
    ecs = ECS();
}

Game::~Game() {

}


void Game::initSystem() {

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
}


void Game::run() {
    initSystem();
    currentState = GameState::ACTIVE;
    loadResources();

    ecs.registerComponent<TransformComponent>();
    systems.emplace_back(ecs.registerSystem<MovementSystem>());

    player = ecs.createEntity();
    Archetype archetype;
    archetype.set(ecs.getComponentID<TransformComponent>());
    ecs.setSystemArchetype<MovementSystem>(archetype);

    ecs.addComponent(player, TransformComponent{2, 2});

    loop();
}

void Game::loop() {

    Uint32 lastUpdate = 0;


    while (currentState == GameState::ACTIVE) {
        processInput();

        for (const auto &system: systems) {
            system->update();
        }

        Uint64 start = SDL_GetPerformanceCounter();

        Uint32 current = SDL_GetTicks();

        //TODO convert to normal looking phys based movement system
        float dT = (current - lastUpdate) / 256.0f;

        lastUpdate = current;

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
        switch (evnt.type) {
            case SDL_QUIT:
                currentState = GameState::EXIT;
                break;
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
            default:
                break;
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}

void Game::loadResources() {
    //player = new Player(TextureManager::loadTexture("char.png", renderer));
}

//void Game::renderEntity(Player *pPlayer) {
//    SDL_Rect dest;
//
//    dest.x = pPlayer->xPos;
//    dest.y = pPlayer->yPos;
//    dest.h = 64;
//    dest.w = 64;
//
//    SDL_RenderCopy(renderer, pPlayer->texture, nullptr, &dest);
//}
