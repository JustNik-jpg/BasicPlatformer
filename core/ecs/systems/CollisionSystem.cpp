//
// Created by JustNik on 30 Jun 2022.
//

#include "CollisionSystem.h"
#include "../../Engine.h"
#include "../components/Component.h"

extern Engine engine;

void CollisionSystem::update() {

    for (auto i = entities.begin(); i != entities.end(); ++i) {
        Entity firstCollide = *i;
        for (auto j = i; j != entities.end(); ++j) {
            Entity secondCollide = *j;

            auto &firstRB = engine.ecs->getComponent<RigidBody>(firstCollide);
            auto &secondRB = engine.ecs->getComponent<RigidBody>(secondCollide);

            if (firstCollide != secondCollide && SDL_HasIntersectionF(&firstRB.collisionBox, &secondRB.collisionBox)) {
                if (firstRB.onCollide != nullptr) {
                    firstRB.onCollide(secondCollide);
                }
                if (secondRB.onCollide != nullptr) {
                    secondRB.onCollide(firstCollide);
                }
            }
        }
    }
}
