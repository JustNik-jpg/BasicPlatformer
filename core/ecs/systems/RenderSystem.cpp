//
// Created by JustNik on 29 May 2022.
//

#include <iostream>
#include "RenderSystem.h"
#include "../ECS.h"
#include "../components/Component.h"

extern ECS ecs;

void RenderSystem::update() {
    for (auto const &entity: entities) {
        auto &transformComponent = ecs.getComponent<TransformComponent>(entity);
        auto &renderComponent = ecs.getComponent<RenderComponent>(entity);
        renderComponent.dest.x = transformComponent.x;
        renderComponent.dest.y = transformComponent.y;

        SDL_RenderCopy(renderer, renderComponent.texture, &renderComponent.src, &renderComponent.dest);


        std::cout << entity << "\n" << transformComponent.x << " " << transformComponent.y << "\n";
    }
}

void RenderSystem::setRenderer(SDL_Renderer *_renderer) {
    this->renderer = _renderer;
}


