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
    registerComponent<ControlComponent>();
    registerComponent<SideComponent>();
    registerComponent<Moving>();
    registerComponent<Following>();
    registerComponent<LifetimeComponent>();
    registerComponent<HealthComponent>();
    registerComponent<DeathComponent>();
    registerComponent<AttackComponent>();
    registerComponent<EntityState>();
    registerComponent<EnemyAIComponent>();
    registerComponent<AnimationComponent>();
}

Entity ECS::createEntity() {
    return entityManager->createEntity();
}

void ECS::destroyEntity(Entity entity) {
    if (hasArchetype<DeathComponent>(entity)) {
        auto &death = getComponent<DeathComponent>(entity);
        death.onDestroy();
    }
    entityManager->deleteEntity(entity);
    componentManager->entityDestroyed(entity);
    systemManager->entityDestroyed(entity);
}

std::vector<Entity> const &ECS::getAliveEntities() {
    return entityManager->getAliveEntities();
}
