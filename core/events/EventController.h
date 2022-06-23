//
// Created by JustNik on 5 Jun 2022.
//

#pragma once

#include <vector>
#include "handlers/IEventHandler.h"

class EventController {
public:
    void processEvents(SDL_Event &event);
    void addEventHandler(IEventHandler *handler);

private:
    std::vector<IEventHandler *> handlers;
};
