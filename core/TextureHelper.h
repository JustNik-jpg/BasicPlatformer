//
// Created by JustNik on 3 Apr 2022.
//

#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <map>
#include "ecs/components/Component.h"
#include "ecs/Types.h"
#include "tilemap/Tile.h"

class TextureHelper {

public:
    static void loadGameTextures();
    static SDL_Texture *getTileTexture(TileType type);
    static SDL_Texture *loadTexture(const char *fileName);
    static SDL_Texture *getBackgroundTexture();
    static SDL_Texture *getTexture(const std::string &name);
    static SDL_Texture *getHealthTexture();

private:

    static std::map<std::string, SDL_Texture *> textureMap;

};
