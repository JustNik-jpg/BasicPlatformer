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
    static Sprite *getTileTexture(TileType type);
    static SDL_Texture *loadTexture(const char *fileName);
    static void unloadTextures();
    static Sprite *getBackgroundTexture();
    static Sprite *getTexture(const std::string &name);
    static Sprite *getHealthTexture();

private:

    static std::map<std::string, Sprite *> textureMap;
};
