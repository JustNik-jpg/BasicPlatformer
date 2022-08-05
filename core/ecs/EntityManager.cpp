//
// Created by JustNik on 16 May 2022.
//

#include "EntityManager.h"
#include <iostream>


EntityManager::EntityManager() {
    livingEntityCount = 0;
    // Initialize the queue with all possible entity IDs to reuse id's
    //when entity is destroyed
    for (Entity entity = 1; entity < MAX_ENTITIES; ++entity) {
        availableEntities.push(entity);
    }
}

Entity EntityManager::createEntity() {
    if (livingEntityCount >= MAX_ENTITIES) {
        std::cout << "Entity limit reached! Can't create new entity, returning NULL entity" << std::endl;
        return NULL_ENTITY;
    }

    // Take an ID from the front of the queue
    Entity id = availableEntities.front();
    availableEntities.pop();
    ++livingEntityCount;
    aliveEntities.push_back(id);

    return id;
}

void EntityManager::deleteEntity(Entity entity) {
    if (entity > MAX_ENTITIES || entity < 0) {
        std::cout << "Trying to delete unknown entity: " << entity << std::endl;
        return;
    }

    // Invalidate the destroyed entity's signature
    archetypes[entity].reset();

    // Put the destroyed ID at the back of the queue
    availableEntities.push(entity);
    --livingEntityCount;
    aliveEntities.erase(std::remove(aliveEntities.begin(), aliveEntities.end(), entity), aliveEntities.end());
}

void EntityManager::setArchetype(Entity entity, Archetype archetype) {
    if (entity > MAX_ENTITIES || entity < 0) {
        std::cout << "Trying to set archetype of an unknown entity: " << entity << std::endl;
        return;
    }
    archetypes[entity] = archetype;
}

Archetype EntityManager::getArchetype(Entity entity) {
    if (entity > MAX_ENTITIES || entity < 0) {
        std::cout << "Trying to get archetype of an unknown entity: " << entity << " returning NULL entity archetype"
                  << std::endl;
        return archetypes[NULL_ENTITY];
    }
    return archetypes[entity];
}

std::vector<Entity> const &EntityManager::getAliveEntities() {
    return aliveEntities;
}
