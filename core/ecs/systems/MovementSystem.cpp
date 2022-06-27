//
// Created by JustNik on 16 May 2022.
//

#include <iostream>
#include "MovementSystem.h"
#include "../ECS.h"
#include "../components/Component.h"
#include "../../Engine.h"

extern Engine engine;

void MovementSystem::update() {
    for (auto const &entity: entities) {
        auto &transformComponent = engine.ecs->getComponent<TransformComponent>(entity);
        auto &rigidBody = engine.ecs->getComponent<RigidBody>(entity);

        auto *colBox = &rigidBody.collisionBox;

        engine.roomController->validatePos(colBox, rigidBody.velocity, rigidBody.standing);
        transformComponent.x = rigidBody.collisionBox.x = std::clamp(rigidBody.velocity.x + rigidBody.collisionBox.x,
                                                                     0.f,
                                                                     1280.f - rigidBody.collisionBox.w);
        transformComponent.y = rigidBody.collisionBox.y = std::clamp(rigidBody.velocity.y + rigidBody.collisionBox.y,
                                                                     -100.f,
                                                                     768.f - rigidBody.collisionBox.h);
    }
}
