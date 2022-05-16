//
// Created by JustNik on 16 May 2022.
//

#include "IComponentArray.h"

template<typename T>
void ComponentArray<T>::insertData(Entity entity, T component) {
    // Put new entry at end and update the maps
    size_t newIndex = size;
    mEntityToIndexMap[entity] = newIndex;
    mIndexToEntityMap[newIndex] = entity;
    mComponentArray[newIndex] = component;
    ++size;
}

template<typename T>
void ComponentArray<T>::removeData(Entity entity) {
    // Copy element at end into deleted element's place to maintain density
    size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
    size_t indexOfLastElement = size - 1;
    mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

    // Update map to point to moved spot
    Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
    mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
    mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

    mEntityToIndexMap.erase(entity);
    mIndexToEntityMap.erase(indexOfLastElement);

    --size;
}

template<typename T>
T &ComponentArray<T>::getData(Entity entity) {
    return mComponentArray[mEntityToIndexMap[entity]];
}

template<typename T>
void ComponentArray<T>::entityDestroyed(Entity entity) {
    if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
        // Remove the entity's component if it existed
        removeData(entity);
    }
}

template<typename T>
ComponentArray<T>::ComponentArray() {
    size = 0;
}
