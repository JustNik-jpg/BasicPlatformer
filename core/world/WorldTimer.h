//
// Created by JustNik on 3 Aug 2022.
//

#pragma once

#include <SDL_timer.h>

class WorldTimer {
public:
    WorldTimer();
    void tick();
    float getDeltaTime() const;
private:
    float deltaTime;
    Uint64 last;
    Uint64 now;
};
