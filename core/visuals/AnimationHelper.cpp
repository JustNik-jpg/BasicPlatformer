//
// Created by JustNik on 6 Jul 2022.
//

#include "AnimationHelper.h"
#include "../Engine.h"
#include "../TextureHelper.h"

extern Engine engine;

AnimationComponent AnimationHelper::getPlayerAttackAnimation() {
    std::map<AnimationState, std::pair<int, std::vector<SDL_Rect>>> animations;
    animations[AnimationState::Attacking] = std::make_pair<int, std::vector<SDL_Rect>>(4, {
            SDL_Rect{0, 0, 48, 80},
            SDL_Rect{48, 0, 48, 80},
            SDL_Rect{96, 0, 48, 80},
            SDL_Rect{144, 0, 48, 80}
    });

    return AnimationComponent{AnimationState::Attacking, animations, 0, TextureHelper::getTexture("weapon")};
}

AnimationComponent AnimationHelper::getPlayerAnimations() {
    std::map<AnimationState, std::pair<int, std::vector<SDL_Rect>>> animations;
    animations[AnimationState::Running] = std::make_pair<int, std::vector<SDL_Rect>>(8, {
            SDL_Rect{0, 0, 48, 80},
            SDL_Rect{48, 0, 48, 80},
            SDL_Rect{96, 0, 48, 80},
            SDL_Rect{144, 0, 48, 80}
    });
    animations[AnimationState::Idle] = std::make_pair<int, std::vector<SDL_Rect>>(64, {
            SDL_Rect{0, 80, 48, 80},
            SDL_Rect{48, 80, 48, 80},
    });
    animations[AnimationState::Attacking] = std::make_pair<int, std::vector<SDL_Rect>>(1, {
            SDL_Rect{0, 160, 48, 80},
            SDL_Rect{48, 160, 48, 80},
            SDL_Rect{96, 160, 48, 80},
            SDL_Rect{144, 160, 48, 80}
    });
    animations[AnimationState::Midair] = std::make_pair<int, std::vector<SDL_Rect>>(1, {
            SDL_Rect{0, 240, 48, 80},
    });

    return AnimationComponent{AnimationState::Attacking, animations, 0, TextureHelper::getTexture("player_anims")};
}

AnimationComponent AnimationHelper::getEnemyAnimations() {
    std::map<AnimationState, std::pair<int, std::vector<SDL_Rect>>> animations;
    animations[AnimationState::Running] = std::make_pair<int, std::vector<SDL_Rect>>(8, {
            SDL_Rect{0, 0, 48, 80},
            SDL_Rect{48, 0, 48, 80},
    });
    animations[AnimationState::Idle] = std::make_pair<int, std::vector<SDL_Rect>>(32, {
            SDL_Rect{0, 80, 48, 80},
            SDL_Rect{48, 80, 48, 80},
            SDL_Rect{96, 80, 48, 80},
    });
    animations[AnimationState::Midair] = std::make_pair<int, std::vector<SDL_Rect>>(2, {
            SDL_Rect{0, 160, 48, 80},
    });

    return AnimationComponent{AnimationState::Idle, animations, 0, TextureHelper::getTexture("enemy_anims")};
}