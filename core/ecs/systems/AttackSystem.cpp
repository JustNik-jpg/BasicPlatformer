//
// Created by JustNik on 29 Jun 2022.
//

#include "AttackSystem.h"
#include "../../Engine.h"
#include "../components/Component.h"

extern Engine engine;

void AttackSystem::update() {
    for (auto const &entity: entities) {
        auto &attackComponent = engine.ecs->getComponent<AttackComponent>(entity);
        if (attackComponent.attacking) {
            if (attackComponent.damagingEntity == NULL_ENTITY) {
                attackComponent.damagingEntity = engine.entityHelper->createPlayerAttackEntity(entity);
                engine.ecs->getComponent<TransformComponent>(attackComponent.damagingEntity).directions = attackComponent.attackDirection;
                attackComponent.lastAttackedOn = SDL_GetTicks();
            } else if (attackComponent.lastAttackedOn + attackComponent.attackCD < SDL_GetTicks()) {
                attackComponent.attacking = false;
                attackComponent.damagingEntity = NULL_ENTITY;
            }
        }
    }
}
