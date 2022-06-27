//
// Created by JustNik on 27 Jun 2022.
//

#include <iostream>
#include "ControlSystem.h"
#include "../../Engine.h"
#include "../components/Component.h"

extern Engine engine;

void ControlSystem::update() {
    for (auto const &entity: entities) {
        auto &rigidBody = engine.ecs->getComponent<RigidBody>(entity);
        auto &controlComponent = engine.ecs->getComponent<ControlComponent>(entity);

        //TODO: move forces to constants

        if (rigidBody.velocity.x < 10 && rigidBody.velocity.x > -10) {
            rigidBody.velocity.x = 10 * controlComponent.control.x;
        }
        if (controlComponent.control.y != 0 && rigidBody.standing) {
            rigidBody.velocity.y = 20 * controlComponent.control.y;
        }

    }
}
