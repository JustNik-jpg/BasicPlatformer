//
// Created by JustNik on 16 May 2022.
//

#include "SystemManager.h"

void SystemManager::entityDestroyed(Entity entity) {
    // Erase a destroyed entity from all system lists
    // mEntities is a set so no check needed
    for (auto const &pair: systems) {
        auto const &system = pair.second;

        system->entities.erase(entity);
    }
}

void SystemManager::entityArchetypeChanged(Entity entity, Archetype archetype) {
    // Notify each system that an entity's archetype changed
    for (auto const &pair: systems) {
        auto const &type = pair.first;
        auto const &system = pair.second;
        auto const &systemArchetype = archetypes[type];

        // Entity archetype matches system signature - insert into set
        if ((archetype & systemArchetype) == systemArchetype) {
            system->entities.insert(entity);
        }
            // Entity archetype does not match system signature - erase from set
        else {
            system->entities.erase(entity);
        }
    }
}

std::unordered_map<const char *, std::shared_ptr<System>> SystemManager::getSystems() {
    return systems;
}
