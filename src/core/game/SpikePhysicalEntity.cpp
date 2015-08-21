//
//  SpikePhysicalEntity.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/20/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "SpikePhysicalEntity.h"

SpikePhysicalEntity::SpikePhysicalEntity(float x, float y, float width, float height, float angle, Environment_Type type) : PhysicalEntity(x, y, width, height, angle)
{
    m_type = type;
}

Environment_Type SpikePhysicalEntity::getType()
{
    return m_type;
}