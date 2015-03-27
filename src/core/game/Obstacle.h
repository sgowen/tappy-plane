//
//  Obstacle.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__Obstacle__
#define __tappyplane__Obstacle__

#include "GameObject.h"
#include "SpikeGameObject.h"
#include "Triangle.h"
#include <vector>
#include <memory>

class PlaneDynamicGameObject;

class Obstacle : public GameObject
{
public:
    Obstacle(float x, float y, float width, float height, float speed, Environment_Type environmentType);
    
    // Return true if the plane has passed this obstacle
    bool update(float deltaTime, PlaneDynamicGameObject &plane);
    
    std::vector<std::unique_ptr<SpikeGameObject>> & getSpikes();

private:
    std::vector<std::unique_ptr<SpikeGameObject>> m_spikes;
    std::unique_ptr<Triangle> m_topBounds;
    std::unique_ptr<Triangle> m_bottomBounds;
    Environment_Type m_environmentType;
    float m_fSpeed;
    float m_fTopBoundsLowestPointY;
    float m_fBottomBoundsHighestPointY;
    bool m_isPassed;
    
    void reset(float x);
};

#endif /* defined(__tappyplane__Obstacle__) */