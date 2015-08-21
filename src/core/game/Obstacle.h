//
//  Obstacle.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/11/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__Obstacle__
#define __tappyplane__Obstacle__

#include "PhysicalEntity.h"
#include "Triangle.h"
#include "EnvironmentType.h"
#include "SpikePhysicalEntity.h"
#include <vector>
#include <memory>

class PlanePhysicalEntity;

class Obstacle : public PhysicalEntity
{
public:
    Obstacle(float x, float y, float width, float height, float speed, Environment_Type environmentType);
    
    // Return true if the plane has passed this obstacle
    bool update(float deltaTime, PlanePhysicalEntity &plane);
    
    std::vector<std::unique_ptr<SpikePhysicalEntity>> & getSpikes();
    
    Triangle & getTopBounds();
    
    Triangle & getBottomBounds();

private:
    std::vector<std::unique_ptr<SpikePhysicalEntity>> m_spikes;
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