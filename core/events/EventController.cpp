//
// Created by JustNik on 5 Jun 2022.
//

#include "EventController.h"

void EventController::processEvents(SDL_Event &event) {
    for (const auto& handler: this->handlers) {
        handler(event);
    }
}

void EventController::addEventHandler(const handler& handler) {
    this->handlers.push_back(handler);
}

