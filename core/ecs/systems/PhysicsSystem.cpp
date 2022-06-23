//
// Created by JustNik on 21 Jun 2022.
//

#include "PhysicsSystem.h"
#include "../../Engine.h"
#include "../components/Component.h"

extern Engine engine;

void PhysicsSystem::update() {
    for (auto const &entity: entities) {
        auto &rigidBody = engine.ecs->getComponent<RigidBody>(entity);

        if (rigidBody.velocity.y < 50) {
            rigidBody.velocity.y += 1;
        }

    }
}
