//
// Created by JustNik on 9 Jun 2022.
//

#pragma once

#include "IEventHandler.h"
#include "../../ecs/Types.h"


class PlayerControlHandler : public IEventHandler {

public:
    explicit PlayerControlHandler(Entity player) : player(player) {};

public:
    void handleEvent(SDL_Event &event) override;

private:
    Entity player;
};
