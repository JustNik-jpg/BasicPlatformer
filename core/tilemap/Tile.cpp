//
// Created by JustNik on 12 Jul 2022.
//
#include "Tile.h"
#include "../TextureHelper.h"
#include "../Engine.h"

extern Engine engine;

std::map<TileType, Tile> TileHelper::tileTemplates = std::map<TileType, Tile>();

Tile TileHelper::setupTileAtPos(TileType type, int x, int y) {
    Tile tile = TileHelper::tileTemplates.at(type);
    tile.collisionBox.x = tile.tile.x = x;
    tile.collisionBox.y = tile.tile.y = y;
    return tile;
}

void TileHelper::initTileTemplates() {
    TileHelper::tileTemplates = std::map<TileType, Tile>{
            {AIR,   Tile{false, false, nullptr, SDL_FRect{0, 0, 32, 32}, SDL_FRect{0, 0, 32, 32}}},
            {EXIT,  Tile{false, true, TextureHelper::getTileTexture(EXIT), SDL_FRect{0, 0, 64, 96}, SDL_FRect{0, 0, 64, 96}, []() {
                if (engine.roomController->getEnemyCount() < 1) {
                    engine.roomController->loadRandomRoom();
                }
            }}},
            {BRICK, Tile{true, false, TextureHelper::getTileTexture(BRICK), SDL_FRect{0, 0, 32, 32}, SDL_FRect{0, 0, 32, 32}}},
            {STONE, Tile{true, false, TextureHelper::getTileTexture(STONE), SDL_FRect{0, 0, 32, 32}, SDL_FRect{0, 0, 32, 32}}}
    };
}
