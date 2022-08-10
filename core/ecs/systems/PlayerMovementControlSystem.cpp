//
// Created by JustNik on 10 Aug 2022.
//

#include "PlayerMovementControlSystem.h"
#include "../../Engine.h"

extern Engine engine;

void PlayerMovementControlSystem::update() {
    Entity player = engine.entityHelper->getPlayer();
    if (player != NULL_ENTITY && engine.ecs->hasArchetype<ControlComponent>(player)) {
        auto &cc = engine.ecs->getComponent<ControlComponent>(player);
        FVector2D controls;
        const Uint8 *state = SDL_GetKeyboardState(nullptr);
        if (state[SDL_SCANCODE_A]) {
            controls.x--;
        }
        if (state[SDL_SCANCODE_D]) {
            controls.x++;
        }
        if (state[SDL_SCANCODE_SPACE]) {
            controls.y--;
        }
        cc.control = controls;
    }
}
