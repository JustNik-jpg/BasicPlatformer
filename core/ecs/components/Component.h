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

struct RenderComponent {
    SDL_Texture *texture;
    SDL_Rect src;  //Texture size
    SDL_FRect dest; //On screen size
};

struct RigidBody {
    SDL_FRect collisionBox;
    FVector2D velocity;
    bool standing;
};

struct SideComponent {
};

struct ControlComponent {
    FVector2D control;
};