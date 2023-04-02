//
// Created by JustNik on 22 Jan 2023.
//

#pragma once

#include <queue>
#include "../ecs/components/Component.h"

class RenderController {

    struct QueuedRenderTexture {
        Sprite *sprite;
        SDL_FRect *dest;
        SDL_RendererFlip flip;
        int priority;
    };

    struct RenderQueueComparator {
        bool
        operator()(const QueuedRenderTexture &first, const QueuedRenderTexture &second) const {
            return first.priority > second.priority;
        }
    };

public:
    void AddToRenderQueue(Sprite *sprite, SDL_FRect *dest, int priority,
                          SDL_RendererFlip flip = SDL_FLIP_NONE);

    void Render();
    int windowW;
    int windowH;

private:
    std::priority_queue<QueuedRenderTexture, std::vector<QueuedRenderTexture>, RenderQueueComparator> renderQueue;
};
