//
//  World.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/10/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__World__
#define __tappyplane__World__

#include <memory>
#include <vector>
#include "Obstacle.h"

class PhysicalEntity;
class Obstacle;
class PlanePhysicalEntity;
class TouchEvent;

class World
{
public:
    World();
    
    void startGame();
    
    void update(float deltaTime);
    
    void handleTouchUp(TouchEvent &touchEvent);
    
    std::vector<std::unique_ptr<Obstacle>> & getObstacles();
    
    PhysicalEntity& getForegroundLeft();
    
    PhysicalEntity& getForegroundRight();
    
    PlanePhysicalEntity & getPlane();
    
    Environment_Type getEnvironmentType();
    
    int getScore();
    
    bool isGameOver();
    
private:
    std::vector<std::unique_ptr<Obstacle>> m_obstacles;
    std::unique_ptr<PlanePhysicalEntity> m_plane;
    std::unique_ptr<PhysicalEntity> m_foregroundLeft;
    std::unique_ptr<PhysicalEntity> m_foregroundRight;
    Environment_Type m_environmentType;
    int m_iScore;
};

#endif /* defined(__tappyplane__World__) */