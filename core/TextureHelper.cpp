//
// Created by JustNik on 3 Apr 2022.
//

#include <string>
#include <iostream>
#include "TextureHelper.h"
#include "Engine.h"

extern Engine engine;

//TODO: create texture atlas
std::map<std::string, SDL_Texture *> TextureHelper::textureMap = std::map<std::string, SDL_Texture *>();

void TextureHelper::loadGameTextures() {
    //Background texture
    textureMap["background"] = loadTexture("back.png");

    //Tile textures
    std::string brick = "tile_" + std::to_string(TileType::BRICK);
    textureMap[brick] = loadTexture((brick + ".png").data());
    std::string stone = "tile_" + std::to_string(TileType::STONE);
    textureMap[stone] = loadTexture((stone + ".png").data());
    std::string exit = "tile_" + std::to_string(TileType::EXIT);
    textureMap[exit] = loadTexture((exit + ".png").data());
    textureMap["tile_" + std::to_string(TileType::AIR)] = nullptr;

    //Player texture
    textureMap["player_anims"] = loadTexture("player_anims.png");
    textureMap["weapon"] = loadTexture("attack.png");
    textureMap["health"] = loadTexture("heart.png");

    //Enemy texture
    textureMap["enemy_anims"] = loadTexture("enemy_anims.png");
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

SDL_Texture *TextureHelper::getTexture(const std::string& name) {
    if (!textureMap.contains(name)) {
        std::cout << "Trying to access not registered texture! - " << name << std::endl;
        return nullptr;
    }
    return textureMap.at(name);
}

SDL_Texture *TextureHelper::getTileTexture(TileType type) {
    return getTexture("tile_" + std::to_string(type));
}

SDL_Texture *TextureHelper::getBackgroundTexture() {
    return getTexture("background");
}

SDL_Texture *TextureHelper::getHealthTexture() {
    return getTexture("health");
}

void TextureHelper::unloadTextures() {
    for (auto item : textureMap) {
        SDL_DestroyTexture(item.second);
    }
}
