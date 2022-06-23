//
// Created by JustNik on 16 May 2022.
//

#pragma once

#include <SDL.h>
#include "../../utility/Vector2D.h"

struct TransformComponent {
    float x;
    float y;
};

struct RenderComponent {
    SDL_Texture *texture;
    SDL_Rect src;  //Texture size
    SDL_FRect dest; //On screen size
};

struct RigidBody {
    SDL_FRect collisionBox;
    FVector2D velocity;
};

struct PlayerComponent {
};