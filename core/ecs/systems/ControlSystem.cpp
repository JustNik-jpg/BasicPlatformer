//
// Created by JustNik on 27 Jun 2022.
//

#include <iostream>
#include "ControlSystem.h"
#include "../../Engine.h"
#include "../Constants.h"

extern Engine engine;

void ControlSystem::update() {
    for (auto const &entity: entities) {
        auto &rigidBody = engine.ecs->getComponent<RigidBody>(entity);
        auto &controlComponent = engine.ecs->getComponent<ControlComponent>(entity);

        if (rigidBody.velocity.x < constants::DEFAULT_X_SPEED && rigidBody.velocity.x > -constants::DEFAULT_X_SPEED) {
            rigidBody.velocity.x = constants::DEFAULT_X_SPEED * controlComponent.control.x;
        }
        if (controlComponent.control.y >= -1 && rigidBody.contacts[2]) {
            std::cout<<"Control "<<controlComponent.control.y;
            rigidBody.velocity.y = constants::DEFAULT_JUMP_FORCE * controlComponent.control.y;
        }

    }
}
