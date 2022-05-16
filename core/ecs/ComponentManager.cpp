//
// Created by JustNik on 16 May 2022.
//

#include "ComponentManager.h"

void ComponentManager::entityDestroyed(Entity entity) {
    for (auto const &pair: componentArrays) {
        auto const &component = pair.second;

        component->entityDestroyed(entity);
    }
}
