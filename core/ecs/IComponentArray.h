//
// Created by JustNik on 16 May 2022.
//

#pragma once

#include <unordered_map>
#include "Types.h"

class IComponentArray {
public:
    virtual ~IComponentArray() = default;

    virtual void entityDestroyed(Entity entity) = 0;

};

template<typename T>
class ComponentArray : public IComponentArray {
public:
    ComponentArray();

    void insertData(Entity entity, T component);

    void removeData(Entity entity);

    T &getData(Entity entity);

    void entityDestroyed(Entity entity) override;

private:
    // The packed array of components (of generic type T),
    // set to a specified maximum amount, matching the maximum number
    // of entities allowed to exist simultaneously, so that each entity
    // has a unique spot.
    std::array<T, MAX_ENTITIES> mComponentArray;

    // Map from an entity ID to an array index.
    std::unordered_map<Entity, size_t> mEntityToIndexMap;

    // Map from an array index to an entity ID.
    std::unordered_map<size_t, Entity> mIndexToEntityMap;

    // Total size of valid entries in the array.
    size_t size;
};