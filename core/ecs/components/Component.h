//
// Created by JustNik on 16 May 2022.
//

#pragma once

#include <SDL.h>

struct TransformComponent {
    int x;
    int y;
};

struct RenderComponent {
    SDL_Texture *texture;
    SDL_Rect src;  //Texture size
    SDL_Rect dest; //On screen size
};

struct PlayerComponent {
};