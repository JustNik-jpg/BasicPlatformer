//
// Created by JustNik on 2 Jun 2022.
//

#pragma once

#include <SDL.h>
#include "ECS.h"

class EntityHelper {
public:
    Entity createPlayer();
    Entity createPlayerAttackEntity(Entity owner);
    Entity createEnemy();
    Entity createEnemy(float x, float y);
    Entity getPlayer();

private:
    Entity player = NULL_ENTITY;
};
