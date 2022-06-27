//
// Created by JustNik on 20 Jun 2022.
//

#include <random>
#include <iostream>
#include "RoomController.h"
#include "../TextureManager.h"
#include "../utility/Vector2D.h"
#include "../collision/Collision.h"
#include <fstream>

void RoomController::renderCurrentLevel(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    for (const auto &mapRow: this->tileMap) {
        for (auto tile: mapRow) {
            if (tile != nullptr) {
                SDL_RenderCopyF(renderer, tile->texture, nullptr, &tile->tile);

                //Debug stuff
                //if (tile->texture != nullptr) {
                //    SDL_RenderFillRectF(renderer, &tile->collisionBox);
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
                                     SDL_FRect{static_cast<float>(x * 32), static_cast<float>(y * 32), 32, 32},
                                     SDL_FRect{static_cast<float>(x * 32), static_cast<float>(y * 32), 32, 32}};
            roomFile.ignore();
        }
    }
}

SDL_Point RoomController::validatePos(SDL_FRect *collider, FVector2D &velocity, bool &standing) {
    SDL_Point result;

    FVector2D cp, cn;
    float t = 0, min_t = INFINITY;
    std::vector<std::pair<std::pair<int, int>, float>> z;

    for (int y = 0; y < tileMap.size(); ++y) {
        for (int x = 0; x < tileMap[y].size(); ++x) {
            if (collision::collideMovingRectWithRect(collider, tileMap[y][x]->collisionBox, velocity, cp, cn, t) &&
                tileMap[y][x]->solid) {
                z.push_back({{y, x}, t});
            }
        }
    }
    if (z.empty()) {
        standing = false;
        return result;
    }

    std::sort(z.begin(), z.end(),
              [](const std::pair<std::pair<int, int>, float> &a, const std::pair<std::pair<int, int>, float> &b) {
                  return a.second < b.second;
              });

    for (auto j: z) {
        collision::resolveCollisionMovingRectWithRect(collider, &tileMap[j.first.first][j.first.second]->collisionBox,
                                                      velocity, standing);
    }

    return result;
}


