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

template<typename T>
void ECS::registerComponent() {
    componentManager->registerComponent<T>();
}

template<typename T>
void ECS::addComponent(Entity entity, T component) {
    componentManager->addComponent(entity, component);
    auto archetype = entityManager->getArchetype(entity);
    archetype.set(componentManager->getComponentID<T>());
    entityManager->setArchetype(entity, archetype);
    systemManager->entityArchetypeChanged(entity, archetype);
}

template<typename T>
void ECS::removeComponent(Entity entity) {
    componentManager->removeComponent<T>(entity);
}

template<typename T>
T &ECS::getComponent(Entity entity) {
    componentManager->getComponent<T>(entity);
}

template<typename T>
ComponentID ECS::getComponentID() {
    return componentManager->getComponentID<T>();
}

template<typename T>
std::shared_ptr<T> ECS::registerSystem() {
    return systemManager->registerSystem<T>();
}

template<typename T>
void ECS::setSystemArchetype(Archetype archetype) {
    systemManager->setArchetype<T>(archetype);
}
