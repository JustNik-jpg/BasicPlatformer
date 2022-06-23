//
// Created by JustNik on 20 Jun 2022.
//

#pragma once

#include <SDL.h>

enum TileType {
    AIR,
    BRICK,
    STONE,
    DOOR
};

struct Tile {
    bool solid;
    SDL_Texture *texture;
    SDL_FRect tile;
    SDL_FRect collisionBox;
};