//
// Created by JustNik on 20 Jun 2022.
//

#pragma once

#include <SDL.h>
#include <functional>
#include <map>
#include "../render/Sprite.h"

enum TileType {
    AIR,
    EXIT,
    BRICK,
    STONE
};

struct Tile {
    bool solid;
    bool interactive;
    Sprite *sprite;
    SDL_FRect tile;
    SDL_FRect collisionBox;
    std::function<void()> onInteract;
};

class TileHelper {
public:
    static Tile setupTileAtPos(TileType type, int x, int y);
    static void initTileTemplates();
    static std::map<TileType, Tile> tileTemplates;
};