//
// Created by JustNik on 2 Jun 2022.
//

#include <iostream>
#include "EntityHelper.h"
#include "components/Component.h"
#include "../RenderHelper.h"
#include "../Engine.h"

extern Engine engine;

Entity EntityHelper::createPlayer() {
    Entity playa = engine.ecs->createEntity();
    std::cout << "Player ID: " << playa << std::endl;
    engine.ecs->addComponent(playa, TransformComponent{0, -16, FVector2D{1, 0}});
    engine.ecs->addComponent(playa, RenderHelper::createPlayerRender());
    engine.ecs->addComponent(playa, RigidBody{SDL_FRect{0, -16, 48, 80}, {0, 0}, nullptr});
    engine.ecs->addComponent(playa, ControlComponent{FVector2D{0, 0}});
    engine.ecs->addComponent(playa, Moving());
    engine.ecs->addComponent(playa, AttackComponent{false, NULL_ENTITY, FVector2D{0, 0}, 0, 1000});
    engine.ecs->addComponent(playa, SideComponent{PLAYER});
    engine.ecs->addComponent(playa, HealthComponent{4, 400});

    player = playa;

    return player;
}

Entity EntityHelper::createPlayerAttackEntity(Entity owner) {
    Entity attack = engine.ecs->createEntity();
    engine.ecs->addComponent(attack, TransformComponent{0, 0, FVector2D{0, 0}});
    engine.ecs->addComponent(attack, RenderHelper::createWeaponRender());
    engine.ecs->addComponent(attack, RigidBody{SDL_FRect{0, 0, 48, 80}, {0, 0}, [this](Entity const &e) {
        if (engine.ecs->hasArchetype<HealthComponent>(e) && engine.ecs->hasArchetype<SideComponent>(e)) {
            auto &sideComponent = engine.ecs->getComponent<SideComponent>(e);
            if (sideComponent.side == Side::ENEMY) {
                --engine.ecs->getComponent<HealthComponent>(e);
            }
        }
    }});
    engine.ecs->addComponent(attack, Following{owner});
    engine.ecs->addComponent(attack, LifetimeComponent{SDL_GetTicks(), 900});

    return attack;
}

Entity EntityHelper::createEnemy() {
    Entity enemy = engine.ecs->createEntity();
    std::cout << "Created enemy with ID: " << enemy << std::endl;

    engine.ecs->addComponent(enemy, TransformComponent{128, -16, FVector2D{1, 0}});
    engine.ecs->addComponent(enemy, RenderHelper::createEnemyRender());
    engine.ecs->addComponent(enemy, RigidBody{SDL_FRect{128, -16, 48, 80}, {0, 0}, [](Entity const &e) {
        if (engine.ecs->hasArchetype<HealthComponent>(e) && engine.ecs->hasArchetype<SideComponent>(e)) {
            auto &sideComponent = engine.ecs->getComponent<SideComponent>(e);
            if (sideComponent.side != Side::ENEMY) {
                --engine.ecs->getComponent<HealthComponent>(e);
            }
        }
    }});
    engine.ecs->addComponent(enemy, ControlComponent{FVector2D{0, 0}});
    engine.ecs->addComponent(enemy, Moving());
    engine.ecs->addComponent(enemy, SideComponent{ENEMY});
    engine.ecs->addComponent(enemy, EnemyAIComponent{Patrolling, 0, FVector2D{128, -16}});
    engine.ecs->addComponent(enemy, HealthComponent{4, 400});

    return enemy;
}

Entity EntityHelper::getPlayer() {
    return player;
}
