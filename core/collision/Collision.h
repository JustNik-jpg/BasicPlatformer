//
// Created by JustNik on 23 Jun 2022.
//

#include "../utility/Vector2D.h"
#include "SDL_rect.h"
#include "../ecs/components/Component.h"

#pragma once

namespace collision {
    bool collideRayWithRect(const FVector2D &rayOrigin, const FVector2D &rayDir, const SDL_FRect *target,
                            FVector2D &contactPoint,
                            FVector2D &contactNormal, float &contactTime);

    bool collideMovingRectWithRect(const SDL_FRect *movingRectangle, const SDL_FRect &staticRectangle,
                                   const FVector2D &velocity,
                                   FVector2D &contactPoint, FVector2D &contactNormal, float &contactTime);


    bool resolveCollisionMovingRectWithRect(RigidBody *movingRect, SDL_FRect *staticRect);
}