//
// Created by JustNik on 17 Apr 2022.
//
#pragma once

#include "ECS.h"

class PositionComponent : public Component {
private:
    int xPos, yPos = 0;

public:
    int getXPos() const {
        return xPos;
    }

    int getYPos() const {
        return yPos;
    }

    void setPos(int x, int y) {
        xPos = x;
        yPos = y;
    }

};