//
// Created by JustNik on 9 Jun 2022.
//

#pragma once

#include "IEventHandler.h"
#include "../../ecs/Types.h"


class PlayerControlHandler : public IEventHandler {

public:
    void handleEvent(SDL_Event &event) override;

};
