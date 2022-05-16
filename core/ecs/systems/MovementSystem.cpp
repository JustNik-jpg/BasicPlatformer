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
        transformComponent.x += 10;
        std::cout << entity << "\n" << transformComponent.x << " " << transformComponent.y << "\n";
    }
}
