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
        //for (const auto &item: UICache) {
        //    delete item;
        //}
        UICache.clear();
        for (int i = 0; i < healthComponent.health; ++i) {

            SDL_FRect& dest = UICache.emplace_back( SDL_FRect{i * 32.f, 0.f, 32.f, 32.f});

            engine.renderController->AddToRenderQueue(TextureHelper::getHealthTexture(), &dest, 10);
        }
    }
}
