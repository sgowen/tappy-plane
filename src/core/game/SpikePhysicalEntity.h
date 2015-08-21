//
//  SpikePhysicalEntity.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/20/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__SpikePhysicalEntity__
#define __tappyplane__SpikePhysicalEntity__

#include "PhysicalEntity.h"
#include "EnvironmentType.h"
#include "Vector2D.h"
#include "Rectangle.h"

class SpikePhysicalEntity : public PhysicalEntity
{
public:
    SpikePhysicalEntity(float x, float y, float width, float height, float angle, Environment_Type type);
    
    Environment_Type getType();
    
private:
    Environment_Type m_type;
};

#endif /* defined(__tappyplane__SpikePhysicalEntity__) */