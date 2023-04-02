//
// Created by JustNik on 22 Jan 2023.
//

#include "RenderController.h"
#include "../Engine.h"

extern Engine engine;

void RenderController::AddToRenderQueue(Sprite *sprite, SDL_FRect *dest, int priority,
                                        SDL_RendererFlip flip) {
    renderQueue.push(QueuedRenderTexture{sprite, dest, flip, priority});
}

void RenderController::Render() {
    SDL_RenderClear(engine.renderer);

    while (!renderQueue.empty()) {
        QueuedRenderTexture renderTarget = renderQueue.top();
        SDL_RenderCopyExF(engine.renderer, renderTarget.sprite->texture, renderTarget.sprite->src, renderTarget.dest, 0,
                          nullptr, renderTarget.flip);
        renderQueue.pop();
    }
    SDL_RenderPresent(engine.renderer);
}
