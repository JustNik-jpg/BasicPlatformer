//
// Created by JustNik on 18 Jul 2022.
//

#include "HealthDisplaySystem.h"
#include "../../Engine.h"
#include "../../TextureHelper.h"

extern Engine engine;

void HealthDisplaySystem::update() {
    Entity player = engine.entityHelper->getPlayer();
    if (player != NULL_ENTITY) {
        auto &healthComponent = engine.ecs->getComponent<HealthComponent>(player);

        for (int i = 0; i < healthComponent.health; ++i) {

            SDL_Rect src = {0, 0, 32, 32};

            SDL_Rect dest = {i * 32, 0, 32, 32};

            SDL_RenderCopy(engine.renderer, TextureHelper::getHealthTexture(), &src, &dest);
        }
    }
}
