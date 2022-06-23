//
// Created by JustNik on 20 Jun 2022.
//

#include <random>
#include <iostream>
#include "RoomController.h"
#include "../TextureManager.h"
#include <fstream>

void RoomController::renderCurrentLevel(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    for (const auto &mapRow: this->tileMap) {
        for (auto tile: mapRow) {
            if (tile != nullptr) {
                SDL_RenderCopy(renderer, tile->texture, nullptr, &tile->tile);

                //Debug stuff
                //if (tile->texture != nullptr) {
                //    SDL_RenderFillRect(renderer, &tile->collisionBox);
                //}
            }
        }
    }

}

void RoomController::loadRandomRoom() {
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(1, 6);
    //loadRoom(distribution(generator));
    loadRoom(0);
}

void RoomController::loadRoom(int levelId) {
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, 2);
    tileMap.resize(24, std::vector<Tile *>(40));
    //for (int y = 0; y < 24; ++y) {
    //    for (int x = 0; x < 40; ++x) {
    //        auto tileChar = TileType(distribution(generator));
    //        tileMap[y][x] = new Tile{tileChar > 0 ? TextureManager::getTileTexture(tileChar) : nullptr, SDL_Rect{x * 32, y * 32, 32, 32},
    //                                 SDL_Rect{x, y, 32, 32}};
    //    }
    //}

    char tileChar;
    std::fstream roomFile;
    std::string path = "../rooms/room" + std::to_string(levelId) + ".txt";
    roomFile.open(path);
    if (roomFile.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Empty room file. Can't load current room...\n";
        return;
    }
    for (int y = 0; y < 24; ++y) {
        for (int x = 0; x < 40; ++x) {
            roomFile.get(tileChar);
            auto tile = TileType((int) tileChar - 48);

            tileMap[y][x] = new Tile{tile > 0, tile > 0 ? TextureManager::getTileTexture(tile) : nullptr,
                                     SDL_Rect{x * 32, y * 32, 32, 32},
                                     SDL_Rect{x * 32, y * 32, 32, 32}};
            roomFile.ignore();
        }
    }
}

bool RoomController::collidesWithTiles(const SDL_Rect &collider) {
    return false;
}

bool checkTopCollision(const SDL_Rect &entityCollider, const SDL_Rect &tileCollider) {
    if ((std::abs((entityCollider.y + entityCollider.h) - tileCollider.y) <= 2) &&
        SDL_HasIntersection(&entityCollider, &tileCollider)) {
        return true;
    }
    return false;
}

bool RoomController::isStanding(const SDL_Rect &collider) {
    if (collider.y + collider.h == 768) {
        return true;
    }
    for (const auto &row: tileMap) {
        for (auto tile: row) {
            if (checkTopCollision(collider, tile->collisionBox) && tile->solid) {
                return true;
            }
        }
    }
    return false;
}

/*
TODO:
 Add proper collision handling to the level
*/
SDL_Point RoomController::validatePos(SDL_Rect &collider) {
    SDL_Point result{collider.x, collider.y};

    return result;
}


