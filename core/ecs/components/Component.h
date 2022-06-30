//
// Created by JustNik on 16 May 2022.
//

#pragma once

#include <SDL.h>
#include "../../utility/Vector2D.h"
#include "../Types.h"

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
    int invulnerableFrames;
    Uint32 damagedOn;

    [[nodiscard]] bool canBeDamaged() const {
        return damagedOn + invulnerableFrames < SDL_GetTicks();
    }

    void dealDamage(int damage) {
        if (canBeDamaged()) {
            health -= damage;
            damagedOn = SDL_GetTicks();
        }
    }

    void restoreHealth(int restore) {
        health += restore;
    }

    void restoreHealth() {
        restoreHealth(1);
    }

    void dealDamage() {
        dealDamage(1);
    }

    HealthComponent &operator--() {
        dealDamage();
        return *this;
    }

    HealthComponent &operator++() {
        restoreHealth();
        return *this;
    }
};

struct DeathComponent {
    std::function<void()> onDestroy;
};

struct AttackComponent {
    bool attacking;
    Entity damagingEntity;
    FVector2D attackDirection;
    Uint32 lastAttackedOn;
    int attackCD;
};