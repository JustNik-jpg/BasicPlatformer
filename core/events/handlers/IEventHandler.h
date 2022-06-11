//
// Created by JustNik on 5 Jun 2022.
//

#pragma once

#include <SDL.h>

class IEventHandler {
public:
    virtual ~IEventHandler() = default;

    virtual void handleEvent(SDL_Event &event) = 0;
};

