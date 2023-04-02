//
// Created by JustNik on 3 Apr 2022.
//

#include <string>
#include <iostream>
#include "TextureHelper.h"
#include "Engine.h"

extern Engine engine;

//TODO: create texture atlas
std::map<std::string, Sprite *> TextureHelper::textureMap = std::map<std::string, Sprite *>();

void TextureHelper::loadGameTextures() {
    //Background texture
    textureMap["background"] = new Sprite{loadTexture("back.png"), nullptr};

    //Tile textures
    std::string brick = "tile_" + std::to_string(TileType::BRICK);
    textureMap[brick] = new Sprite{loadTexture((brick + ".png").data()), nullptr};
    std::string stone = "tile_" + std::to_string(TileType::STONE);
    textureMap[stone] = new Sprite{loadTexture((stone + ".png").data()), nullptr};
    std::string exit = "tile_" + std::to_string(TileType::EXIT);
    textureMap[exit] = new Sprite{loadTexture((exit + ".png").data()), nullptr};
    textureMap["tile_" + std::to_string(TileType::AIR)] = nullptr;

    //Player texture
    textureMap["player_anims"] = new Sprite{loadTexture("player_anims.png"), nullptr};
    textureMap["weapon"] = new Sprite{loadTexture("attack.png"), nullptr};
    textureMap["health"] = new Sprite{loadTexture("heart.png"), nullptr};

    //Enemy texture
    textureMap["enemy_anims"] = new Sprite{loadTexture("enemy_anims.png"), nullptr};
}

SDL_Texture *TextureHelper::loadTexture(const char *fileName) {
    std::string path = "../assets/";
    //The final texture
    SDL_Texture *newTexture = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.append(fileName).c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(engine.renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from " << path.c_str() << "! SDL Error: " << SDL_GetError()
                      << std::endl;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

Sprite *TextureHelper::getTexture(const std::string& name) {
    if (!textureMap.contains(name)) {
        std::cout << "Trying to access not registered texture! - " << name << std::endl;
        return nullptr;
    }
    return textureMap.at(name);
}

Sprite *TextureHelper::getTileTexture(TileType type) {
    return getTexture("tile_" + std::to_string(type));
}

Sprite *TextureHelper::getBackgroundTexture() {
    return getTexture("background");
}

Sprite *TextureHelper::getHealthTexture() {
    return getTexture("health");
}

void TextureHelper::unloadTextures() {
    for (const auto& item : textureMap) {
        SDL_DestroyTexture(item.second->texture);
        delete item.second;
    }
    textureMap.clear();
}
