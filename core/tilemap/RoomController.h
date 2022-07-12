//
// Created by JustNik on 20 Jun 2022.
//

#pragma once

#include <vector>
#include "Tile.h"
#include "../utility/Vector2D.h"
#include "../ecs/components/Component.h"

class RoomController {
public:
    void loadRandomRoom();
    void loadRoom(int levelId);
    void renderCurrentLevel(SDL_Renderer *renderer);
    void validatePos(RigidBody *collider);
    FVector2D getLineOfSight(const FVector2D& pos, const FVector2D& dir);
    void processInteraction(RigidBody *collider);

private:
    Tile getTileFromType(TileType type, int x, int y);
    std::vector<Tile> tileMap;
};
