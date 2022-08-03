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

        if (rigidBody.velocity.y < constants::MAX_FALL_SPEED) {
            rigidBody.velocity.y += constants::GRAVITY_ACCELERATION* engine.worldTimer->getDeltaTime();
        }

        if (rigidBody.velocity.x > 0) {
            rigidBody.velocity.x-= engine.worldTimer->getDeltaTime();
        } else if (rigidBody.velocity.x < 0) {
            rigidBody.velocity.x+= engine.worldTimer->getDeltaTime();
        }

    }
}
