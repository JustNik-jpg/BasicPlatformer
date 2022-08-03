//
// Created by JustNik on 6 Jul 2022.
//
#include "AnimationSystem.h"
#include "../../Engine.h"
#include <iostream>

extern Engine engine;

void AnimationSystem::update() {
    for (auto const &entity: entities) {
        auto &renderComponent = engine.ecs->getComponent<RenderComponent>(entity);
        auto &animationComponent = engine.ecs->getComponent<AnimationComponent>(entity);

        //Changing state
        if (engine.ecs->hasArchetype<AttackComponent>(entity) &&
            engine.ecs->getComponent<AttackComponent>(entity).attacking) {
            animationComponent.changeState(Attacking);
            animationComponent.currentFrame = engine.ecs->getComponent<AttackComponent>(entity).attackStance;
        } else if (engine.ecs->hasArchetype<Moving>(entity) && engine.ecs->hasArchetype<RigidBody>(entity)) {
            auto &rigigdBody = engine.ecs->getComponent<RigidBody>(entity);
            if (rigigdBody.contacts[2]) {
                if (rigigdBody.velocity.x != 0) {
                    animationComponent.changeState(Running);
                } else {
                    animationComponent.changeState(Idle);
                }
            } else {
                animationComponent.changeState(Midair);
            }
        }

        //Setting up rendering animation
        renderComponent.texture = animationComponent.textureSheet;
        auto &animationData = animationComponent.animations[animationComponent.currentState];

        int frameDelay = animationData.first;
        auto &animationFrames = animationData.second;

        if (frameDelay == 0 && animationFrames.empty()) {
            return;
        }

        renderComponent.src = animationFrames[animationComponent.currentFrame / frameDelay];
        animationComponent.currentFrame+= engine.worldTimer->getDeltaTime();
        if (animationComponent.currentFrame >= animationFrames.size() * frameDelay) {
            animationComponent.currentFrame = 0;
        }
    }
}

