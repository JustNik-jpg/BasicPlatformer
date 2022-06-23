//
// Created by JustNik on 3 Apr 2022.
//

#include <string>
#include "TextureManager.h"
#include "Engine.h"

extern Engine engine;

std::map<TileType, SDL_Texture *> TextureManager::tileTextures = std::map<TileType, SDL_Texture *>();

SDL_Texture *TextureManager::loadTexture(const char *fileName) {
    std::string path = "../assets/";
    //The final texture
    SDL_Texture *newTexture = nullptr;

    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(path.append(fileName).c_str());
    if (loadedSurface == nullptr) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
    } else {
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(engine.renderer, loadedSurface);
        if (newTexture == nullptr) {
            printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

SDL_Texture *TextureManager::getTileTexture(TileType type) {
    if (tileTextures.contains(type)) {
        return tileTextures.at(type);
    } else {
        std::string name = "tile_" + std::to_string(type) + ".png";
        return tileTextures[type] = loadTexture(name.data());
    }
}
