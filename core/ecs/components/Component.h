//
// Created by JustNik on 16 May 2022.
//

#pragma once

#include <SDL.h>
#include "../../utility/Vector2D.h"

struct TransformComponent {
    float x;
    float y;
    FVector2D directions;
};

struct Moving {
};

struct Following {
    Entity following;
};

struct RenderComponent {
    SDL_Texture *texture;
    SDL_Rect src;  //Texture size
    SDL_FRect dest; //On screen size
};

struct RigidBody {
    SDL_FRect collisionBox;
    FVector2D velocity;
    std::function<void(Entity const &)> onCollide;
    bool standing;
};

struct ControlComponent {
    FVector2D control;
};

enum Side {
    PLAYER,
    ENEMY,
    ALLY,
};

struct SideComponent {
    Side side;
};

struct LifetimeComponent {
    Uint32 createdOn;
    int lifetime;
};

struct HealthComponent {
    int health;
    Uint32 damagedOn;
    int invulnerableTicks;

    bool canBeDamaged() {
        return damagedOn + invulnerableTicks < SDL_GetTicks();
    }
};

struct DeathComponent {
    std::function<void()> onDestroy;
};

struct AttackComponent {
    bool attacking;
    Entity damagingEntity;
    Uint32 lastAttackedOn;
    int attackCD;
};