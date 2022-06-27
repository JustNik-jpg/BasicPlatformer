//
// Created by JustNik on 2 Jun 2022.
//

#include "EntityHelper.h"
#include "components/Component.h"
#include "../TextureManager.h"

EntityHelper::EntityHelper(ECS *ecs, SDL_Renderer *renderer) {
    this->renderer = renderer;
    this->ecs = ecs;
}

Entity EntityHelper::createPlayer() {
    Entity player = ecs->createEntity();
    ecs->addComponent(player, TransformComponent{0, -16, FVector2D{1, 1}});
    ecs->addComponent(player, RenderComponent{TextureManager::loadTexture("char.png"), SDL_Rect{0, 0, 48, 80},
                                              SDL_FRect{0, 0, 48, 80}});
    ecs->addComponent(player, RigidBody{SDL_FRect{0, -16, 48, 80}, {0, 0}});
    ecs->addComponent(player, ControlComponent{FVector2D{0, 0}});

    return player;
}

Entity EntityHelper::createEnemy() {
    return 0;
}
