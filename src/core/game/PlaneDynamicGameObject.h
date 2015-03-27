//
//  PlaneDynamicGameObject.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/10/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__PlaneDynamicGameObject__
#define __tappyplane__PlaneDynamicGameObject__

#include "DynamicGameObject.h"
#include "PlaneType.h"
#include "PuffCloud.h"
#include <memory>
#include <vector>

class PlaneDynamicGameObject : public DynamicGameObject
{
public:
    PlaneDynamicGameObject(float x, float y, float width, float height);
    
    void update(float deltaTime, float shiftX);
    
    void startFlying();
    
    void ascend();
    
    void hit();
    
    std::vector<std::unique_ptr<PuffCloud>> & getPuffClouds();
    
    float getStateTime();
    
    bool isFlying();
    
    bool isHit();
    
    bool isDead();
    
    Plane_Type getType();

private:
    std::vector<std::unique_ptr<PuffCloud>> m_puffClouds;
    Plane_Type m_type;
    float m_fStateTime;
    float m_fTimeSinceFlap;
    bool m_isFlying;
    bool m_isHit;
    bool m_isDead;
};

#endif /* defined(__tappyplane__PlaneDynamicGameObject__) */