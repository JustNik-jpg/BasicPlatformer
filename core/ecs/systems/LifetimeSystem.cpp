//
// Created by JustNik on 29 Jun 2022.
//

#include "LifetimeSystem.h"
#include "../../Engine.h"
#include "../components/Component.h"

extern Engine engine;

void LifetimeSystem::update() {
    std::vector<Entity> toDelete;
    for (auto const &entity: entities) {
        auto &lifetimeComponent = engine.ecs->getComponent<LifetimeComponent>(entity);
        if (lifetimeComponent.createdOn + lifetimeComponent.lifetime < SDL_GetTicks()) {
            toDelete.emplace_back(entity);
        }
    }
    for (auto entity: toDelete) {
        engine.ecs->destroyEntity(entity);
    }
}
