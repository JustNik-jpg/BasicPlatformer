//
// Created by JustNik on 16 May 2022.
//

#pragma once

#include <unordered_map>
#include <memory>
#include "Types.h"
#include "IComponentArray.h"

class ComponentManager {
public:
    template<typename T>
    void registerComponent();

    template<typename T>
    ComponentID getComponentID();

    template<typename T>
    void addComponent(Entity entity, T component);

    template<typename T>
    void removeComponent(Entity entity);

    template<typename T>
    T &getComponent(Entity entity);

    void entityDestroyed(Entity entity);

private:
    // Map from type string pointer to a component type
    std::unordered_map<const char *, ComponentID> componentTypes{};

    // Map from type string pointer to a component array
    std::unordered_map<const char *, std::shared_ptr<IComponentArray>> componentArrays{};

    // The component ID to be assigned to the next registered component - starting at 0
    ComponentID nextComponentID{};

    // Convenience function to get the statically cast pointer to the ComponentArray of type T.
    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray();
};