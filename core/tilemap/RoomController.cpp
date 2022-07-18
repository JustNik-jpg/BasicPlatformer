//
// Created by JustNik on 20 Jun 2022.
//

#include <random>
#include <iostream>
#include "RoomController.h"
#include "../TextureHelper.h"
#include "../collision/Collision.h"
#include "../Engine.h"
#include <fstream>
#include <sstream>

extern Engine engine;

void RoomController::renderCurrentLevel(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, TextureHelper::getBackgroundTexture(), nullptr, nullptr);

    //SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    for (const auto &tile: this->tileMap) {
        SDL_RenderCopyF(renderer, tile.texture, nullptr, &tile.tile);
        //Debug stuff
        //if (tile->texture != nullptr) {
        //    SDL_RenderFillRectF(renderer, &tile->collisionBox);
        //}
    }

}

void RoomController::loadRandomRoom() {
    std::random_device generator;
    std::uniform_int_distribution<int> distribution(0, 1);
    int roomNumber = distribution(generator);
    std::cout << "Loading room " << roomNumber << ".." << std::endl;
    loadRoom(roomNumber);
}

void RoomController::loadRoom(int levelId) {
    tileMap.clear();
    currentEnemyCount = 0;

    std::ifstream roomFile;
    std::string path = "../rooms/room" + std::to_string(levelId) + ".txt";
    roomFile.open(path);
    if (roomFile.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Empty room file. Can't load current room..." << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << roomFile.rdbuf();

    std::istringstream fileStream(buffer.str());

    parseRoom(fileStream);
    parsePlayerStartPos(fileStream);
    parseEnemies(fileStream);
}

void RoomController::validatePos(RigidBody *collider) {
    FVector2D cp, cn;
    float t = 0, min_t = INFINITY;
    std::vector<std::pair<int, float>> z;

    for (int i = 0; i < tileMap.size(); ++i) {
        if (collision::collideMovingRectWithRect(&collider->collisionBox, tileMap[i].collisionBox,
                                                 collider->velocity, cp, cn, t) &&
            tileMap[i].solid) {
            z.emplace_back(i, t);
        }
    }

    collider->contacts[0] = false;
    collider->contacts[1] = false;
    collider->contacts[2] = false;
    collider->contacts[3] = false;

    if (z.empty()) {
        return;
    }

    std::sort(z.begin(), z.end(),
              [](const std::pair<int, float> &a, const std::pair<int, float> &b) {
                  return a.second < b.second;
              });

    for (auto j: z) {
        collision::resolveCollisionMovingRectWithRect(collider, &tileMap[j.first].collisionBox);
    }
}

FVector2D RoomController::getLineOfSight(const FVector2D &pos, const FVector2D &dir) {
    std::map<float, FVector2D> contactMap;

    FVector2D finalDir = dir * 300;
    for (const auto &tile: tileMap) {
        FVector2D contactPoint, contactNormal;
        float contactTime;
        bool contact = collision::collideRayWithRect(pos, finalDir, &tile.collisionBox, contactPoint,
                                                     contactNormal, contactTime);
        contactPoint.y = pos.y;
        if (contact && tile.solid) {
            contactMap[contactTime] = contactPoint;
        }
    }

    return contactMap.begin()->second;
}

void RoomController::processInteraction(RigidBody *collider) {
    //TODO: handle room exit
    for (const auto &tile: tileMap) {
        if (SDL_HasIntersectionF(&tile.collisionBox, &collider->collisionBox) && tile.interactive) {
            if (tile.onInteract != nullptr) {
                tile.onInteract();
            }
        }
    }
}

void RoomController::enemyDied() {
    currentEnemyCount--;
}

int RoomController::getEnemyCount() const {
    return currentEnemyCount;
}

void RoomController::parseEnemies(std::istringstream &roomFile) {

    int numberOfEnemies;
    roomFile >> numberOfEnemies;

    for (int i = 0; i < numberOfEnemies; ++i) {
        float x, y;
        roomFile >> x;
        roomFile.ignore();
        roomFile >> y;
        roomFile.ignore();
        engine.entityHelper->createEnemy(x, y);
        currentEnemyCount++;
    }
}

void RoomController::parsePlayerStartPos(std::istringstream &roomFile) {
    float x, y;
    roomFile >> x;
    roomFile.ignore();
    roomFile >> y;
    roomFile.ignore();

    Entity entity = engine.entityHelper->getPlayer();
    if (entity != NULL_ENTITY && engine.ecs->hasArchetype<RigidBody>(entity) &&
        engine.ecs->hasArchetype<TransformComponent>(entity)) {
        auto &rigidBody = engine.ecs->getComponent<RigidBody>(entity);
        auto &transform = engine.ecs->getComponent<TransformComponent>(entity);

        transform.x = rigidBody.collisionBox.x = x;
        transform.y = rigidBody.collisionBox.y = y;
    }
}

void RoomController::parseRoom(std::istringstream &roomFile) {
    char tileType;

    for (int y = 0; y < 24; ++y) {
        for (int x = 0; x < 40; ++x) {
            roomFile.get(tileType);
            auto type = TileType((int) tileType - 48);
            tileMap.emplace_back(TileHelper::setupTileAtPos(type, x * 32, y * 32));
            roomFile.ignore();
        }
    }
}
