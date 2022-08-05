//
// Created by JustNik on 16 May 2022.
//

#pragma once

#include <queue>
#include "Types.h"

class EntityManager {
public:
    EntityManager();
    Entity createEntity();
    void deleteEntity(Entity entity);
    void setArchetype(Entity entity, Archetype archetype);
    Archetype getArchetype(Entity entity);
    std::vector<Entity> const &getAliveEntities();

private:
    std::uint32_t livingEntityCount;
    std::queue<Entity> availableEntities;
    std::vector<Entity> aliveEntities;
    std::array<Archetype, MAX_ENTITIES> archetypes;
};
