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
    void registerComponent() {
        const char *typeName = typeid(T).name();


        // Add this component type to the component type tileTextures
        componentTypes.insert({typeName, nextComponentID});

        // Create a ComponentArray pointer and add it to the component arrays tileTextures
        componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

        // Increment the value so that the next component registered will be different
        ++nextComponentID;
    }

    template<typename T>
    ComponentID getComponentID() {
        const char *typeName = typeid(T).name();

        // Return this component's type - used for creating archetypes
        return componentTypes[typeName];
    }

    template<typename T>
    void addComponent(Entity entity, T component) {
        getComponentArray<T>()->insertData(entity, component);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        getComponentArray<T>()->removeData(entity);
    }

    template<typename T>
    T &getComponent(Entity entity) {
        return getComponentArray<T>()->getData(entity);
    }

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
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
        const char *typeName = typeid(T).name();

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }
};