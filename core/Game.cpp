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
#include "ecs/systems/PhysicsSystem.h"
#include "ecs/systems/ControlSystem.h"
#include "ecs/systems/AttackSystem.h"
#include "ecs/systems/LifetimeSystem.h"
#include "ecs/systems/FollowSystem.h"
#include "ecs/systems/CollisionSystem.h"
#include "ecs/systems/DeathSystem.h"
#include "ecs/systems/EnemyAISystem.h"
#include "ecs/systems/AnimationSystem.h"

Engine engine;

Game::Game() {
}

Game::~Game() {

}


void Game::initGame() {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized SDL successfully" << std::endl;
    } else {
        std::cout << "Something went wrong when initializing SDL..." << "\n" << &SDL_GetErrorMsg << std::endl;
    }
    engine.window = SDL_CreateWindow("Basic gameussy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 768, 0);

    if (!engine.window) {
        std::cout << "Something went wrong creating the window... " << "\n" << &SDL_GetErrorMsg << std::endl;
    }

    engine.renderer = SDL_CreateRenderer(engine.window, -1, 0);
    if (!engine.renderer) {
        std::cout << "Something went wrong creating the renderer... " << "\n" << &SDL_GetErrorMsg << std::endl;
    }
    TextureHelper::loadGameTextures();
    TileHelper::initTileTemplates();
    engine.ecs = new ECS();
    engine.eventController = new EventController();
    engine.ecs->init();
    initSystems();
    engine.entityHelper = new EntityHelper();
    engine.roomController = new RoomController();
}


void Game::run() {
    initGame();
    currentState = GameState::ACTIVE;

    engine.entityHelper->createPlayer();
    engine.roomController->loadRandomRoom();
    engine.eventController->addEventHandler(new PlayerControlHandler());

    loop();
}

void Game::loop() {

    //Uint32 lastUpdate = 0;

    while (currentState == GameState::ACTIVE) {
        processInput();
        engine.roomController->renderCurrentLevel(engine.renderer);
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
    systems.emplace_back(engine.ecs->registerSystem<LifetimeSystem>());
    systems.emplace_back(engine.ecs->registerSystem<ControlSystem>());
    systems.emplace_back(engine.ecs->registerSystem<PhysicsSystem>());
    systems.emplace_back(engine.ecs->registerSystem<AttackSystem>());
    systems.emplace_back(engine.ecs->registerSystem<MovementSystem>());
    systems.emplace_back(engine.ecs->registerSystem<EnemyAISystem>());
    systems.emplace_back(engine.ecs->registerSystem<CollisionSystem>());
    systems.emplace_back(engine.ecs->registerSystem<FollowSystem>());
    systems.emplace_back(engine.ecs->registerSystem<DeathSystem>());
    systems.emplace_back(engine.ecs->registerSystem<AnimationSystem>());
    systems.emplace_back(engine.ecs->registerSystem<RenderSystem>());

    Archetype physicsArchetype;
    physicsArchetype.set(engine.ecs->getComponentID<RigidBody>());
    engine.ecs->setSystemArchetype<PhysicsSystem>(physicsArchetype);

    Archetype movementArchetype;
    movementArchetype.set(engine.ecs->getComponentID<TransformComponent>());
    movementArchetype.set(engine.ecs->getComponentID<RigidBody>());
    movementArchetype.set(engine.ecs->getComponentID<Moving>());
    engine.ecs->setSystemArchetype<MovementSystem>(movementArchetype);

    Archetype renderArchetype;
    renderArchetype.set(engine.ecs->getComponentID<TransformComponent>());
    renderArchetype.set(engine.ecs->getComponentID<RenderComponent>());
    engine.ecs->setSystemArchetype<RenderSystem>(renderArchetype);

    Archetype controlArchetype;
    controlArchetype.set(engine.ecs->getComponentID<RigidBody>());
    controlArchetype.set(engine.ecs->getComponentID<ControlComponent>());
    engine.ecs->setSystemArchetype<ControlSystem>(controlArchetype);

    Archetype followArchetype;
    followArchetype.set(engine.ecs->getComponentID<RigidBody>());
    followArchetype.set(engine.ecs->getComponentID<TransformComponent>());
    followArchetype.set(engine.ecs->getComponentID<Following>());
    engine.ecs->setSystemArchetype<FollowSystem>(followArchetype);

    Archetype attackArchetype;
    attackArchetype.set(engine.ecs->getComponentID<AttackComponent>());
    engine.ecs->setSystemArchetype<AttackSystem>(attackArchetype);

    Archetype lifetimeArchetype;
    lifetimeArchetype.set(engine.ecs->getComponentID<LifetimeComponent>());
    engine.ecs->setSystemArchetype<LifetimeSystem>(lifetimeArchetype);

    Archetype collisionArchetype;
    collisionArchetype.set(engine.ecs->getComponentID<RigidBody>());
    engine.ecs->setSystemArchetype<ControlSystem>(collisionArchetype);

    Archetype deathArchetype;
    deathArchetype.set(engine.ecs->getComponentID<HealthComponent>());
    engine.ecs->setSystemArchetype<DeathSystem>(deathArchetype);

    Archetype enemyAIArchetype;
    enemyAIArchetype.set(engine.ecs->getComponentID<EnemyAIComponent>());
    enemyAIArchetype.set(engine.ecs->getComponentID<RigidBody>());
    enemyAIArchetype.set(engine.ecs->getComponentID<TransformComponent>());
    engine.ecs->setSystemArchetype<EnemyAISystem>(enemyAIArchetype);

    Archetype animationArchetype;
    animationArchetype.set(engine.ecs->getComponentID<AnimationComponent>());
    animationArchetype.set(engine.ecs->getComponentID<RenderComponent>());
    engine.ecs->setSystemArchetype<AnimationSystem>(animationArchetype);
}
