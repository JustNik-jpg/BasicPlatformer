#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

class ECS {
public:
    void init();

    Entity createEntity();

    void destroyEntity(Entity entity);
    std::vector<Entity> const &getAliveEntities();


    // Component methods
    template<typename T>
    void registerComponent() {
        componentManager->registerComponent<T>();
    }

    template<typename T>
    void addComponent(Entity entity, T component) {
        componentManager->addComponent(entity, component);
        auto archetype = entityManager->getArchetype(entity);
        archetype.set(componentManager->getComponentID<T>());
        entityManager->setArchetype(entity, archetype);
        systemManager->entityArchetypeChanged(entity, archetype);
    }

    template<typename T>
    bool hasArchetype(Entity entity) {
        auto archetype = entityManager->getArchetype(entity);
        return archetype.test(componentManager->getComponentID<T>());
    }

    template<typename T>
    void removeComponent(Entity entity) {
        componentManager->removeComponent<T>(entity);
    }

    template<typename T>
    T &getComponent(Entity entity) {
        return componentManager->getComponent<T>(entity);
    }

    template<typename T>
    ComponentID getComponentID() {
        return componentManager->getComponentID<T>();
    }


    // System methods
    template<typename T>
    std::shared_ptr<T> registerSystem() {
        return systemManager->registerSystem<T>();
    }

    template<typename T>
    void setSystemArchetype(Archetype archetype) {
        systemManager->setArchetype<T>(archetype);
    }

private:
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<SystemManager> systemManager;
};
