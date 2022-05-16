#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

class ECS {
public:
    void init();

    Entity createEntity();

    void destroyEntity(Entity entity);


    // Component methods
    template<typename T>
    void registerComponent();

    template<typename T>
    void addComponent(Entity entity, T component);

    template<typename T>
    void removeComponent(Entity entity);

    template<typename T>
    T &getComponent(Entity entity);

    template<typename T>
    ComponentID getComponentID();


    // System methods
    template<typename T>
    std::shared_ptr<T> registerSystem();

    template<typename T>
    void setSystemArchetype(Archetype archetype);

private:
    std::unique_ptr<ComponentManager> componentManager;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<SystemManager> systemManager;
};
