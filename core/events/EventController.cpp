//
// Created by JustNik on 5 Jun 2022.
//

#include "EventController.h"

void EventController::processEvents(SDL_Event &event) {
    for (auto handler: this->handlers) {
        handler->handleEvent(event);
    }
}

void EventController::addEventHandler(IEventHandler *handler) {
    this->handlers.push_back(handler);
}
