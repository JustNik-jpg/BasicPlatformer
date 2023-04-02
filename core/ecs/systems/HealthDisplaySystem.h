//
// Created by JustNik on 18 Jul 2022.
//

#pragma once

#include <vector>
#include "System.h"
#include "SDL_rect.h"

class HealthDisplaySystem : public System {
protected:
    std::vector<SDL_FRect> UICache;
public :
    void update() override;
};
