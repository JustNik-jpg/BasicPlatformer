//
// Created by JustNik on 2 Jul 2022.
//

#include <iostream>
#include <random>
#include "EnemyAISystem.h"
#include "../../Engine.h"
#include "../components/Component.h"
#include "../../collision/Collision.h"

extern Engine engine;

void EnemyAISystem::update() {
    if (engine.entityHelper->getPlayer() == NULL_ENTITY) {
        return;
    }
    for (auto const &entity: entities) {
        auto &aiComponent = engine.ecs->getComponent<EnemyAIComponent>(entity);
        auto &rigidBody = engine.ecs->getComponent<RigidBody>(entity);
        auto &transform = engine.ecs->getComponent<TransformComponent>(entity);
        auto &controlComponent = engine.ecs->getComponent<ControlComponent>(entity);

        //Checking if the enemy see the player
        FVector2D eyeLevel = FVector2D{rigidBody.collisionBox.x + (rigidBody.collisionBox.w / 2),
                                       rigidBody.collisionBox.y + 4};

        auto lineOfSight = engine.roomController->getLineOfSight(eyeLevel, transform.directions);

        auto playerRigidBody = engine.ecs->getComponent<RigidBody>(engine.entityHelper->getPlayer());

        FVector2D contactPoint, contactNormal;
        float contactTime;

        bool collision = collision::collideRayWithRect(eyeLevel, FVector2D{lineOfSight.x - eyeLevel.x, 0},
                                                       &playerRigidBody.collisionBox, contactPoint,
                                                       contactNormal, contactTime);
        collision = collision && contactTime <= 1 && contactTime >= 0;

        //Changing state depending on if entity seen
        switch (aiComponent.state) {
            case Patrolling:
                if (collision) {
                    aiComponent.state = Chasing;
                    std::cout << "Changing state to chasing" << std::endl;

                }
                break;
            case Chasing:
                if (!collision) {
                    aiComponent.state = Seeking;
                    aiComponent.lastSeenTime = SDL_GetTicks();
                    std::cout << "Changing state to seeking" << std::endl;

                }
                break;
            case Seeking:
                if (aiComponent.lastSeenTime + 1000 < SDL_GetTicks()) {
                    aiComponent.state = Patrolling;
                    std::cout << "Changing state to patrolling" << std::endl;

                }
                break;
        }

        //Processing state
        //TODO: maybe need some rework because enemies are stupid now
        // they need to see more and react better to obstacles and player getting out os sight
        switch (aiComponent.state) {
            case Patrolling:
                if (rigidBody.collisionBox.x < aiComponent.currentDestination.x + 5 &&
                    rigidBody.collisionBox.x > aiComponent.currentDestination.x - 5) {
                    std::random_device generator;
                    std::uniform_real_distribution<float> distribution(rigidBody.collisionBox.x - 100.f,
                                                                       rigidBody.collisionBox.x + 100.f);
                    aiComponent.currentDestination.x = std::clamp(distribution(generator), 0.f, 1280.f);
                    aiComponent.startPathAfter = SDL_GetTicks() + 3000;
                } else if (aiComponent.startPathAfter < SDL_GetTicks()) {
                    if (aiComponent.startPathAfter + 20000 < SDL_GetTicks()) {
                        aiComponent.currentDestination.x = rigidBody.collisionBox.x;
                    }
                    controlComponent.control.x =
                            std::copysign(1.f, aiComponent.currentDestination.x - rigidBody.collisionBox.x) * 0.5f;
                    if (rigidBody.contacts[1] || rigidBody.contacts[3]) {
                        controlComponent.control.y--;
                    } else {
                        controlComponent.control.y = 0;
                    }
                }
                break;
            case Chasing:
            case Seeking:
                aiComponent.currentDestination.x = aiComponent.chasePosSeen.x =
                        playerRigidBody.collisionBox.x + playerRigidBody.collisionBox.w / 2;
                aiComponent.currentDestination.y = aiComponent.chasePosSeen.y = playerRigidBody.collisionBox.y;

                controlComponent.control.x =
                        std::copysign(1.f, aiComponent.currentDestination.x - rigidBody.collisionBox.x) * 0.5f;
                if (rigidBody.contacts[1] || rigidBody.contacts[3]) {
                    controlComponent.control.y = -1;
                } else {
                    controlComponent.control.y = 0;
                }
                break;
        }


        if (rigidBody.collisionBox.x < aiComponent.currentDestination.x + 5 &&
            rigidBody.collisionBox.x > aiComponent.currentDestination.x - 5) {
            controlComponent.control.x = 0;
        }
    }
}
