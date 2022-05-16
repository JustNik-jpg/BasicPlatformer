//
// Created by JustNik on 16 May 2022.
//

#pragma once

#include <memory>
#include <unordered_map>
#include "Types.h"
#include "systems/System.h"

class SystemManager {
public:
    template<typename T>
    std::shared_ptr<T> registerSystem() {
        const char *typeName = typeid(T).name();

        // Create a pointer to the system and return it, so it can be used externally
        auto system = std::make_shared<T>();
        systems.insert({typeName, system});
        return system;
    }

    template<typename T>
    void setArchetype(Archetype signature) {
        const char *typeName = typeid(T).name();

        // Set the signature for this system
        archetypes.insert({typeName, signature});
    }

    void entityDestroyed(Entity entity);

    void entityArchetypeChanged(Entity entity, Archetype archetype);

private:
    // Map from system names to a signature
    std::unordered_map<const char *, Archetype> archetypes{};

    // Map from system names to a system pointer
    std::unordered_map<const char *, std::shared_ptr<System>> systems{};
};

