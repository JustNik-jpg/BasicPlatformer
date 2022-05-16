//
// Created by JustNik on 16 May 2022.
//

#include "ECS.h"

void ECS::init() {
    componentManager = std::make_unique<ComponentManager>();
    entityManager = std::make_unique<EntityManager>();
    systemManager = std::make_unique<SystemManager>();
}

Entity ECS::createEntity() {
    return entityManager->createEntity();
}

void ECS::destroyEntity(Entity entity) {
    entityManager->deleteEntity(entity);
    componentManager->entityDestroyed(entity);
    systemManager->entityDestroyed(entity);
}
