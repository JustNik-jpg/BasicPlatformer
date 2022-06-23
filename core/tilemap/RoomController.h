//
// Created by JustNik on 20 Jun 2022.
//

#pragma once

#include <vector>
#include "Tile.h"

class RoomController {
public:
    void loadRandomRoom();

    void loadRoom(int levelId);

    void renderCurrentLevel(SDL_Renderer *renderer);

    bool collidesWithTiles(const SDL_Rect &collider);

    bool isStanding(const SDL_Rect &collider);

    SDL_Point validatePos(SDL_Rect &collider);

private:
    std::vector<std::vector<Tile *>> tileMap;
};
