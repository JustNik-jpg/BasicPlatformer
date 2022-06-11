//
// Created by JustNik on 9 Jun 2022.
//

#include "PlayerControlHandler.h"
#include "SDL.h"
#include "../../ecs/ECS.h"
#include "../../ecs/components/Component.h"

extern ECS ecs;

void PlayerControlHandler::handleEvent(SDL_Event &event) {
    auto &rigidBody = ecs.getComponent<RigidBody>(player);

    if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                rigidBody.ySpeed -= 10;
                break;
            case SDLK_s:
                rigidBody.ySpeed += 10;
                break;
            case SDLK_a:
                rigidBody.xSpeed -= 10;
                break;
            case SDLK_d:
                rigidBody.xSpeed += 10;
                break;
        }

    } else if (event.type == SDL_KEYUP && event.key.repeat == 0) {
        switch (event.key.keysym.sym) {
            case SDLK_w:
                rigidBody.ySpeed += 10;
                break;
            case SDLK_s:
                rigidBody.ySpeed -= 10;
                break;
            case SDLK_a:
                rigidBody.xSpeed += 10;
                break;
            case SDLK_d:
                rigidBody.xSpeed -= 10;
                break;
        }
    }
}
