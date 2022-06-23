//
// Created by JustNik on 20 Jun 2022.
//

#pragma once

#include <vector>
#include "Tile.h"
#include "../utility/Vector2D.h"

class RoomController {
public:
    void loadRandomRoom();

    void loadRoom(int levelId);

    void renderCurrentLevel(SDL_Renderer *renderer);

    SDL_Point validatePos(SDL_FRect *collider, FVector2D &velocity);

private:
    std::vector<std::vector<Tile *>> tileMap;
};
