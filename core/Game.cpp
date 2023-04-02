//
// Created by JustNik on 3 Apr 2022.
//

#include "Game.h"
#include "iostream"
#include "ecs/systems/MovementSystem.h"
#include "ecs/systems/RenderSystem.h"
#include "ecs/components/Component.h"
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
#include "ecs/systems/HealthDisplaySystem.h"
#include "ecs/systems/PlayerMovementControlSystem.h"

Engine engine;

Game::Game() {
    initGame();
    currentState = GameState::INITIALIZED;
}

Game::~Game() {
    delete engine.ecs;
    delete engine.eventController;
    delete engine.entityHelper;
    delete engine.roomController;
    delete engine.worldTimer;
    delete engine.renderController;

    SDL_DestroyRenderer(engine.renderer);
    SDL_DestroyWindow(engine.window);
    TextureHelper::unloadTextures();
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
    engine.worldTimer = new WorldTimer();
    engine.renderController = new RenderController();
    //TODO: this needs to be thought out
    engine.renderController->windowW = 1280;
    engine.renderController->windowH = 768;
}


void Game::run() {
    currentState = GameState::ACTIVE;

    engine.roomController->start();
    engine.eventController->addEventHandler([](SDL_Event &evnt) {
        Entity player = engine.entityHelper->getPlayer();
        if (evnt.key.keysym.sym == SDLK_r && evnt.key.repeat == 0 && evnt.type == SDL_KEYDOWN) {
            engine.roomController->restart();
        }

        if (player != NULL_ENTITY && evnt.key.repeat == 0) {
            auto &rigidBody = engine.ecs->getComponent<RigidBody>(player);
            auto &controlComponent = engine.ecs->getComponent<ControlComponent>(player);
            switch (evnt.type) {
                case SDL_KEYDOWN:
                    switch (evnt.key.keysym.sym) {
                        //case SDLK_SPACE:
                        //    controlComponent.control.y--;
                        //    break;
                        //case SDLK_a:
                        //    controlComponent.control.x--;
                        //    break;
                        //case SDLK_d:
                        //    controlComponent.control.x++;
                        //    break;
                        case SDLK_e:
                            engine.roomController->processInteraction(&rigidBody);
                            break;
                    }
                    break;
                //case SDL_KEYUP:
                //    switch (evnt.key.keysym.sym) {
                //        case SDLK_SPACE:
                //            controlComponent.control.y++;
                //            break;
                //        case SDLK_a:
                //            controlComponent.control.x++;
                //            break;
                //        case SDLK_d:
                //            controlComponent.control.x--;
                //            break;
                //    }
                //    break;
                case SDL_MOUSEBUTTONDOWN :
                    auto &attackComponent = engine.ecs->getComponent<AttackComponent>(player);
                    switch (evnt.button.button) {
                        case SDL_BUTTON_LEFT:
                            attackComponent.attacking = true;
                            attackComponent.attackDirection.x = -1;
                            break;
                        case SDL_BUTTON_RIGHT:
                            attackComponent.attacking = true;
                            attackComponent.attackDirection.x = 1;

                            break;
                    }
                    break;
            }
        }
    });
    engine.eventController->addEventHandler([this](SDL_Event &evnt) {
        if (evnt.type == SDL_QUIT) {
            this->currentState = GameState::EXIT;
        }
    });

    loop();
}

void Game::loop() {
    while (currentState == GameState::ACTIVE) {
        processInput();
        engine.roomController->renderCurrentLevel(engine.renderer);
        for (const auto &system: systems) {
            system->update();
        }
        engine.worldTimer->tick();
        render();
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
    engine.renderController->Render();
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
    systems.emplace_back(engine.ecs->registerSystem<HealthDisplaySystem>());
    systems.emplace_back(engine.ecs->registerSystem<PlayerMovementControlSystem>());


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
