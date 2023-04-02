//
// Created by JustNik on 29 May 2022.
//

#include "RenderSystem.h"
#include "../ECS.h"
#include "../components/Component.h"
#include "../../Engine.h"

extern Engine engine;

void RenderSystem::update() {
    for (auto const &entity: entities) {
        auto &transformComponent = engine.ecs->getComponent<TransformComponent>(entity);
        auto &renderComponent = engine.ecs->getComponent<RenderComponent>(entity);
        renderComponent.dest.x = transformComponent.x;
        renderComponent.dest.y = transformComponent.y;

        //Debug stuff
        //auto &rigidBody = engine.ecs->getComponent<RigidBody>(entity);
        //SDL_SetRenderDrawColor(engine.renderer, 255,0,0, 255);
        //SDL_RenderFillRectF(engine.renderer, &rigidBody.collisionBox);
        engine.renderController->AddToRenderQueue(renderComponent.sprite, &renderComponent.dest,
                                                  1, transformComponent.directions.x < 0 ? SDL_FLIP_HORIZONTAL
                                                                                         : SDL_FLIP_NONE);
    }
}


