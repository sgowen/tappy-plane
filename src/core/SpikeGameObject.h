//
//  SpikeGameObject.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/20/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__SpikeGameObject__
#define __tappyplane__SpikeGameObject__

#include "GameObject.h"
#include "EnvironmentType.h"
#include "Vector2D.h"
#include "Rectangle.h"

class SpikeGameObject : public GameObject
{
public:
    SpikeGameObject(float x, float y, float width, float height, float angle, Environment_Type type);
    
    Environment_Type getType();
    
private:
    Environment_Type m_type;
};

#endif /* defined(__tappyplane__SpikeGameObject__) */