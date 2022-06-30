//
// Created by JustNik on 2 Jun 2022.
//

#pragma once

#include <SDL.h>
#include "ECS.h"

class EntityHelper {
public:
    EntityHelper(ECS* ecs, SDL_Renderer *renderer);
    Entity createPlayer();
    Entity createPlayerAttackEntity(Entity owner);
    Entity createEnemy();

private:
    ECS* ecs;
    SDL_Renderer *renderer;
};
