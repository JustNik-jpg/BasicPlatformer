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

        //if (engine.roomController->isStanding(rigidBody.collisionBox)) {
        //    if (rigidBody.ySpeed > 0) {
        //        rigidBody.ySpeed = 0;
        //    }
        //} else {
        //    if (rigidBody.ySpeed < 50) {
        //        rigidBody.ySpeed += 1;
        //    }
        //}

    }
}
