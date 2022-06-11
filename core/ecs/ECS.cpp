//
// Created by JustNik on 16 May 2022.
//

#include "ECS.h"
#include "components/Component.h"

void ECS::init() {
    componentManager = std::make_unique<ComponentManager>();
    entityManager = std::make_unique<EntityManager>();
    systemManager = std::make_unique<SystemManager>();

    registerComponent<TransformComponent>();
    registerComponent<RenderComponent>();
    registerComponent<RigidBody>();
}

Entity ECS::createEntity() {
    return entityManager->createEntity();
}

void ECS::destroyEntity(Entity entity) {
    entityManager->deleteEntity(entity);
    componentManager->entityDestroyed(entity);
    systemManager->entityDestroyed(entity);
}
