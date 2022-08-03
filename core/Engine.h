//
// Created by JustNik on 11 Jun 2022.
//

#pragma once

#include "ecs/EntityHelper.h"
#include "events/EventController.h"
#include "tilemap/RoomController.h"
#include "world/WorldTimer.h"

struct Engine {
    RoomController *roomController;
    EntityHelper *entityHelper;
    SDL_Renderer *renderer;
    SDL_Window *window;
    ECS* ecs;
    EventController* eventController;
    WorldTimer* worldTimer;
};
