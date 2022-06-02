//
// Created by JustNik on 2 Jun 2022.
//

#include "EntityHelper.h"
#include "components/Component.h"
#include "../TextureManager.h"


EntityHelper::EntityHelper(ECS* ecs, SDL_Renderer *renderer) {
    this->renderer = renderer;
    this->ecs = ecs;
}

Entity EntityHelper::createPlayer() {
    Entity player = ecs->createEntity();
    ecs->addComponent(player, TransformComponent{2, 2});
    ecs->addComponent(player, RenderComponent{TextureManager::loadTexture("char.png", renderer), SDL_Rect{0, 0, 64, 64},SDL_Rect{0, 0, 64, 64}});
    return player;
}

Entity EntityHelper::createEnemy() {
    return 0;
}