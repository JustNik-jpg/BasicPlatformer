//
// Created by JustNik on 16 May 2022.
//

#pragma once

#include <set>
#include "../Types.h"

class System {
public:
    virtual void update() = 0;
    std::set<Entity> entities;
};
