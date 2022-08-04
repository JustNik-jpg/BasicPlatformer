//
// Created by JustNik on 5 Jun 2022.
//

#pragma once

#include <vector>
#include <functional>
#include <functional>
#include "SDL_events.h"

typedef std::function<void(SDL_Event & )> handler;

class EventController {
public:
    void processEvents(SDL_Event &event);
    void addEventHandler(const handler& handler);

private:
    std::vector<handler> handlers;
};
