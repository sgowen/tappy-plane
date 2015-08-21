//
//  Glove.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "Glove.h"
#include "Vector2D.h"
#include "Rectangle.h"

Glove::Glove(float x, float y, float width, float height) : PhysicalEntity(x, y, width, height, 0)
{
    // Empty
}

void Glove::update(float deltaTime)
{
    Entity::update(deltaTime);
}