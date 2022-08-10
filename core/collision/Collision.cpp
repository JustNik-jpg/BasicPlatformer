//
// Created by JustNik on 4 Jul 2022.
//
#include <iostream>
#include "Collision.h"

bool collision::collideRayWithRect(const FVector2D &rayOrigin, const FVector2D &rayDir, const SDL_FRect *target,
                                   FVector2D &contactPoint, FVector2D &contactNormal, float &contactTime) {
    contactNormal = {0, 0};
    contactPoint = {0, 0};

    // Cache division
    FVector2D invdir = 1.0f / rayDir;

    // Calculate intersections with rectangle bounding axes
    FVector2D t_near = (FVector2D(target->x, target->y) - rayOrigin) * invdir;
    FVector2D t_far = (FVector2D(target->x, target->y) + FVector2D(target->w, target->h) - rayOrigin) * invdir;

    if (std::isnan(t_far.y) || std::isnan(t_far.x)) return false;
    if (std::isnan(t_near.y) || std::isnan(t_near.x)) return false;

    // Sort distances
    if (t_near.x > t_far.x) std::swap(t_near.x, t_far.x);
    if (t_near.y > t_far.y) std::swap(t_near.y, t_far.y);

    // Early rejection
    if (t_near.x > t_far.y || t_near.y > t_far.x) return false;

    // Closest 'time' will be the first contact
    contactTime = std::max(t_near.x, t_near.y);

    // Furthest 'time' is contact on opposite side of target
    float t_hit_far = std::min(t_far.x, t_far.y);

    // Reject if ray direction is pointing away from object
    if (t_hit_far < 0)
        return false;

    // Contact point of collision from parametric line equation
    contactPoint = rayOrigin + contactTime * rayDir;

    if (t_near.x > t_near.y) {
        if (invdir.x < 0) {
            contactNormal = {1, 0};
        } else {
            contactNormal = {-1, 0};
        }
    } else if (t_near.x < t_near.y) {
        if (invdir.y < 0) {
            contactNormal = {0, 1};
        } else {
            contactNormal = {0, -1};
        }
    }

    // Note if t_near == t_far, collision is principly in a diagonal
    // so pointless to resolve. By returning a CN={0,0} even though its
    // considered a hit, the resolver won't change anything.
    return true;
}

bool collision::collideMovingRectWithRect(const SDL_FRect *movingRectangle, const SDL_FRect &staticRectangle,
                                          const FVector2D &velocity, FVector2D &contactPoint, FVector2D &contactNormal,
                                          float &contactTime) {
    // Check if dynamic rectangle is actually moving assuming rectangles are NOT in collision from start
    if (velocity.x == 0 && velocity.y == 0)
        return false;

    // Expand target rectangle by source dimensions
    SDL_FRect expanded_target(staticRectangle);

    expanded_target.x = staticRectangle.x - movingRectangle->w / 2;
    expanded_target.w = staticRectangle.w + movingRectangle->w;

    expanded_target.y = staticRectangle.y - movingRectangle->h / 2;
    expanded_target.h = staticRectangle.h + movingRectangle->h;

    if (collideRayWithRect(FVector2D(movingRectangle->x, movingRectangle->y) +
                           FVector2D(movingRectangle->w, movingRectangle->h) / 2,
                           velocity,
                           &expanded_target, contactPoint, contactNormal, contactTime))
        return (contactTime >= 0.0f && contactTime < 1.0f);
    else
        return false;
}

bool collision::resolveCollisionMovingRectWithRect(RigidBody *movingRect, float dT, SDL_FRect *staticRect) {
    FVector2D contactPoint, contactNormal;
    float contactTime = 0.0f;
    if (collideMovingRectWithRect(&movingRect->collisionBox, *staticRect, movingRect->velocity*dT, contactPoint,
                                  contactNormal,
                                  contactTime)) {
        if (contactNormal.y > 0) {
            movingRect->contacts[0] = true; //top

        }
        if (contactNormal.x < 0) {
            movingRect->contacts[1] = true; //right

        }
        if (contactNormal.y < 0) {
            movingRect->contacts[2] = true; //bot
        }
        if (contactNormal.x > 0) {
            movingRect->contacts[3] = true; //left

        }


        if (contactNormal.x != 0) {
            if (contactNormal.x > 0) {
                movingRect->collisionBox.x = staticRect->x + staticRect->w;
            } else {
                movingRect->collisionBox.x = staticRect->x - movingRect->collisionBox.w;
            }
            movingRect->velocity.x = 0;
        } else if (contactNormal.y != 0) {
            if (contactNormal.y > 0) {
                movingRect->collisionBox.y = staticRect->y + staticRect->h;
            } else {
                movingRect->collisionBox.y = staticRect->y - movingRect->collisionBox.h;
            }
            movingRect->velocity.y = 0;
        }
        return true;
    }

    return false;
}
