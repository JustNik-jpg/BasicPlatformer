//
// Created by JustNik on 3 Aug 2022.
//

#include <iostream>
#include "WorldTimer.h"

void WorldTimer::tick() {
    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime = (((now - last) * 1000) / static_cast<float>(SDL_GetPerformanceFrequency()));
    std::cout << (deltaTime * 0.001) << std::endl;
}

WorldTimer::WorldTimer() {
    now = SDL_GetPerformanceCounter();
    last = 0;
    deltaTime = 0;
}

float WorldTimer::getDeltaTime() const {
    return deltaTime *0.05f;
}
