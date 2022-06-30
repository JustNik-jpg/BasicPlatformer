//
// Created by JustNik on 29 Jun 2022.
//

#include "FollowSystem.h"
#include "../../Engine.h"
#include "../components/Component.h"

extern Engine engine;

void FollowSystem::update() {
    for (auto const &entity: entities) {
        auto &followComponent = engine.ecs->getComponent<Following>(entity);
        auto &transform = engine.ecs->getComponent<TransformComponent>(entity);
        auto &rigidBody = engine.ecs->getComponent<RigidBody>(entity);


        auto &ownerTransform = engine.ecs->getComponent<TransformComponent>(followComponent.following);
        auto &ownerRigidBody = engine.ecs->getComponent<RigidBody>(followComponent.following);

        transform.directions = ownerTransform.directions;
        transform.x = ownerTransform.x;
        transform.x += ownerTransform.directions.x > 0 ? ownerRigidBody.collisionBox.w : -rigidBody.collisionBox.w;
        transform.y = ownerTransform.y;
    }
}
