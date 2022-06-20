//
// Created by JustNik on 29 May 2022.
//

#include <iostream>
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

        SDL_RenderCopy(engine.renderer, renderComponent.texture, &renderComponent.src, &renderComponent.dest);

        std::cout << entity << "\n" << transformComponent.x << " " << transformComponent.y << "\n";
    }
}


