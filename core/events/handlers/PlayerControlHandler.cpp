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


    //TODO: redo control system because now it's kinda broken with collision system
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                rigidBody.velocity.y -= 20;
                break;
            case SDLK_a:
                rigidBody.velocity.x -= 10;
                break;
            case SDLK_d:
                rigidBody.velocity.x += 10;
                break;
        }

    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_a:
                if (rigidBody.velocity.x <= -10) {
                    rigidBody.velocity.x += 10;
                }
                break;
            case SDLK_d:
                if (rigidBody.velocity.x >= 10) {
                    rigidBody.velocity.x -= 10;
                }
                break;
        }
    }
}
