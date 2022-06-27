//
// Created by JustNik on 9 Jun 2022.
//

#include "PlayerControlHandler.h"
#include "SDL.h"
#include "../../ecs/ECS.h"
#include "../../ecs/components/Component.h"
#include "../../Engine.h"

extern Engine engine;

void PlayerControlHandler::handleEvent(SDL_Event &event) {
    auto &rigidBody = engine.ecs->getComponent<RigidBody>(player);

    auto &controlComponent = engine.ecs->getComponent<ControlComponent>(player);
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                controlComponent.control.y--;
                break;
            case SDLK_a:
                controlComponent.control.x--;
                break;
            case SDLK_d:
                controlComponent.control.x++;
                break;
        }
    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                controlComponent.control.y++;
                break;
            case SDLK_a:
                controlComponent.control.x++;
                break;
            case SDLK_d:
                controlComponent.control.x--;
                break;
        }
    }
}
