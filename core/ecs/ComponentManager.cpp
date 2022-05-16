//
// Created by JustNik on 16 May 2022.
//

#include "ComponentManager.h"

template<typename T>
void ComponentManager::registerComponent() {
    const char *typeName = typeid(T).name();


    // Add this component type to the component type map
    componentTypes.insert({typeName, nextComponentID});

    // Create a ComponentArray pointer and add it to the component arrays map
    componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

    // Increment the value so that the next component registered will be different
    ++nextComponentID;
}

template<typename T>
ComponentID ComponentManager::getComponentID() {
    const char *typeName = typeid(T).name();

    // Return this component's type - used for creating archetypes
    return componentTypes[typeName];
}

template<typename T>
void ComponentManager::addComponent(Entity entity, T component) {
    getComponentArray<T>()->insertData(entity, component);
}

template<typename T>
void ComponentManager::removeComponent(Entity entity) {
    getComponentArray<T>()->removeData(entity);
}

template<typename T>
T &ComponentManager::getComponent(Entity entity) {
    return getComponentArray<T>()->getData(entity);
}

void ComponentManager::entityDestroyed(Entity entity) {
    for (auto const &pair: componentArrays) {
        auto const &component = pair.second;

        component->entityDestroyed(entity);
    }
}

template<typename T>
std::shared_ptr<ComponentArray<T>> ComponentManager::getComponentArray() {
    const char *typeName = typeid(T).name();

    return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
}
