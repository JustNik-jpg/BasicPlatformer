//
// Created by JustNik on 6 Jul 2022.
//

#pragma once

#include "../ecs/components/Component.h"

class AnimationHelper {
public:
    static AnimationComponent getPlayerAttackAnimation();
    static AnimationComponent getPlayerAnimations();
    static AnimationComponent getEnemyAnimations();
};
