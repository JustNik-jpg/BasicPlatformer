//
// Created by JustNik on 29 Jun 2022.
//

#include "LifetimeSystem.h"
#include "../../Engine.h"
#include "../components/Component.h"

extern Engine engine;

void LifetimeSystem::update() {
    for (auto const &entity: entities) {
        auto &lifetimeComponent = engine.ecs->getComponent<LifetimeComponent>(entity);
        if (lifetimeComponent.createdOn + lifetimeComponent.lifetime < SDL_GetTicks()) {
            engine.ecs->destroyEntity(entity);
        }
    }
}
