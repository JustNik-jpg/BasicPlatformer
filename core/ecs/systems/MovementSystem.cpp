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

        rigidBody.collisionBox.x =transformComponent.x = std::clamp(rigidBody.xSpeed + transformComponent.x, 0, 1280 - rigidBody.collisionBox.w);
        rigidBody.collisionBox.y =transformComponent.y = std::clamp(rigidBody.ySpeed + transformComponent.y, 0, 768 -  rigidBody.collisionBox.h);

        std::cout << entity << "\n" << transformComponent.x << " " << transformComponent.y << "\n";
    }
}
