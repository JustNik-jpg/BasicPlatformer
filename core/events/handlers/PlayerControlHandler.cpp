//
// Created by JustNik on 9 Jun 2022.
//

#include <iostream>
#include "PlayerControlHandler.h"
#include "SDL.h"
#include "../../ecs/ECS.h"
#include "../../ecs/components/Component.h"
#include "../../Engine.h"

extern Engine engine;

void PlayerControlHandler::handleEvent(SDL_Event &event) {

    if (event.key.repeat == 0) {
        auto &rigidBody = engine.ecs->getComponent<RigidBody>(player);
        auto &controlComponent = engine.ecs->getComponent<ControlComponent>(player);
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        controlComponent.control.y--;
                        break;
                    case SDLK_a:
                        controlComponent.control.x--;
                        break;
                    case SDLK_d:
                        controlComponent.control.x++;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                        controlComponent.control.y++;
                        break;
                    case SDLK_a:
                        controlComponent.control.x++;
                        break;
                    case SDLK_d:
                        controlComponent.control.x--;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN :
                if (event.button.button == SDL_BUTTON_LEFT) {
                    auto &attackComponent = engine.ecs->getComponent<AttackComponent>(player);
                    attackComponent.attacking = true;
                }
                break;
        }
    }
}
