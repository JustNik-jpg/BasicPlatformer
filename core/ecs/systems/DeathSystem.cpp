//
// Created by JustNik on 30 Jun 2022.
//

#include "DeathSystem.h"
#include "../../Engine.h"
#include "../components/Component.h"

extern Engine engine;

void DeathSystem::update() {
    for (auto const &entity: entities) {
        auto &healthComponent = engine.ecs->getComponent<HealthComponent>(entity);
        if (healthComponent.health <= 0) {
            engine.ecs->destroyEntity(entity);
        }
    }
}
