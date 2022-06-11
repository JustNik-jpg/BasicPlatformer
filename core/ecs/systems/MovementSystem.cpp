//
// Created by JustNik on 16 May 2022.
//

#include <iostream>
#include "MovementSystem.h"
#include "../ECS.h"
#include "../components/Component.h"

extern ECS ecs;

void MovementSystem::update() {
    for (auto const &entity: entities) {
        auto &transformComponent = ecs.getComponent<TransformComponent>(entity);
        auto &rigidBody = ecs.getComponent<RigidBody>(entity);

        transformComponent.x = std::clamp(rigidBody.xSpeed+transformComponent.x,0, 1280-rigidBody.collisionBox.w);
        transformComponent.y = std::clamp(rigidBody.ySpeed+transformComponent.y,0, 720-rigidBody.collisionBox.h);
        std::cout << entity << "\n" << transformComponent.x << " " << transformComponent.y << "\n";
    }
}
