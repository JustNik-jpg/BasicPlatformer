//
// Created by JustNik on 2 Jun 2022.
//

#include "EntityHelper.h"
#include "components/Component.h"
#include "../TextureManager.h"

EntityHelper::EntityHelper(ECS *ecs, SDL_Renderer *renderer) {
    this->renderer = renderer;
    this->ecs = ecs;
}

Entity EntityHelper::createPlayer() {
    Entity player = ecs->createEntity();
    ecs->addComponent(player, TransformComponent{0, -16, FVector2D{1, 1}});
    ecs->addComponent(player, RenderComponent{TextureManager::loadTexture("char.png"), SDL_Rect{0, 0, 48, 80},
                                              SDL_FRect{0, 0, 48, 80}});
    ecs->addComponent(player, RigidBody{SDL_FRect{0, -16, 48, 80}, {0, 0}, nullptr});
    ecs->addComponent(player, ControlComponent{FVector2D{0, 0}});
    ecs->addComponent(player, Moving());
    ecs->addComponent(player, AttackComponent{false, NULL_ENTITY, 0, 1000});

    return player;
}

Entity EntityHelper::createPlayerAttackEntity(Entity owner) {
    Entity attack = ecs->createEntity();
    ecs->addComponent(attack, TransformComponent{0, 0, FVector2D{0, 0}});
    ecs->addComponent(attack, RenderComponent{TextureManager::loadTexture("attack.png"), SDL_Rect{0, 0, 48, 80},
                                              SDL_FRect{0, 0, 48, 80}});
    ecs->addComponent(attack, RigidBody{SDL_FRect{0, 0, 48, 80}, {0, 0}, [this](Entity const &e) {
        if (ecs->hasArchetype<HealthComponent>(e) && ecs->hasArchetype<SideComponent>(e)) {
            auto &healthComponent = ecs->getComponent<HealthComponent>(e);
            auto &sideComponent = ecs->getComponent<SideComponent>(e);
            if (sideComponent.side == Side::ENEMY && ecs->getComponent<HealthComponent>(e).canBeDamaged()) {
                healthComponent.health -= 1;
            }
        }
    }});
    ecs->addComponent(attack, Following{owner});
    ecs->addComponent(attack, LifetimeComponent{SDL_GetTicks(), 900});

    return attack;
}

Entity EntityHelper::createEnemy() {
    return 0;
}
