//
// Created by JustNik on 29 May 2022.
//

#pragma once

#include "System.h"
#include <SDL.h>

class RenderSystem : public System {
public:
    void setRenderer(SDL_Renderer* _renderer);
    void update() override;
private:
    SDL_Renderer* renderer;
};
