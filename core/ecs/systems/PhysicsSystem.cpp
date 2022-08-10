//
// Created by JustNik on 21 Jun 2022.
//

#include "PhysicsSystem.h"
#include "../../Engine.h"
#include "../components/Component.h"
#include "../Constants.h"

extern Engine engine;

void PhysicsSystem::update() {
    for (auto const &entity: entities) {
        auto &rigidBody = engine.ecs->getComponent<RigidBody>(entity);

        rigidBody.velocity.y = std::min(
                rigidBody.velocity.y + (constants::GRAVITY_ACCELERATION * engine.worldTimer->getDeltaTime()),
                constants::MAX_FALL_SPEED);

        if (rigidBody.velocity.x > 0) {
            rigidBody.velocity.x = engine.worldTimer->getDeltaTime() > 1 ? 0 : rigidBody.velocity.x -
                                                                               engine.worldTimer->getDeltaTime();
        } else if (rigidBody.velocity.x < 0) {
            rigidBody.velocity.x = engine.worldTimer->getDeltaTime() > 1 ? 0 : rigidBody.velocity.x +
                                                                               engine.worldTimer->getDeltaTime();
        }

    }
}
