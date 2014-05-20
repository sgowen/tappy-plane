//
//  SpikeGameObject.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/20/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "SpikeGameObject.h"

SpikeGameObject::SpikeGameObject(float x, float y, float width, float height, float angle, Environment_Type type) : GameObject(x, y, width, height, angle)
{
    m_type = type;
}

Environment_Type SpikeGameObject::getType()
{
    return m_type;
}