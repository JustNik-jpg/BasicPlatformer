//
// Created by JustNik on 3 Apr 2022.
//


#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include "tilemap/Tile.h"

#pragma once

class TextureManager {

public:
    static SDL_Texture *loadTexture(const char *fileName);
    static SDL_Texture *getTileTexture(TileType type);

private:
    static std::map<TileType, SDL_Texture*> tileTextures;
};
