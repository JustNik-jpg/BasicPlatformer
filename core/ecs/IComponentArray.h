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

    ComponentArray() {
        size = 0;
    }

    void insertData(Entity entity, T component) {
        // Put new entry at end and update the maps
        size_t newIndex = size;
        mEntityToIndexMap[entity] = newIndex;
        mIndexToEntityMap[newIndex] = entity;
        mComponentArray[newIndex] = component;
        ++size;
    }

    void removeData(Entity entity) {
        // Copy element at end into deleted element's place to maintain density
        size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
        size_t indexOfLastElement = size - 1;
        mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

        // Update tileTextures to point to moved spot
        Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
        mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        mEntityToIndexMap.erase(entity);
        mIndexToEntityMap.erase(indexOfLastElement);

        --size;
    }

    T &getData(Entity entity) {
        return mComponentArray[mEntityToIndexMap[entity]];
    }

    void entityDestroyed(Entity entity) override{
        if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
            // Remove the entity's component if it existed
            removeData(entity);
        }
    }

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