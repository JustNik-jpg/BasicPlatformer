//
// Created by JustNik on 3 Apr 2022.
//


#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include "tilemap/Tile.h"
#include "ecs/components/Component.h"
#include "ecs/Types.h"

#pragma once

class TextureHelper {

public:
    static void loadGameTextures();
    static SDL_Texture *getTileTexture(TileType type);
    static SDL_Texture *loadTexture(const char *fileName);
    static SDL_Texture *getBackgroundTexture();
    static SDL_Texture *getTexture(std::string name);

private:

    static std::map<std::string, SDL_Texture *> textureMap;

};
