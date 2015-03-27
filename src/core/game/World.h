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

class GameObject;
class Obstacle;
class PlaneDynamicGameObject;
class TouchEvent;

class World
{
public:
    World();
    
    void startGame();
    
    void update(float deltaTime);
    
    void handleTouchUp(TouchEvent &touchEvent);
    
    std::vector<std::unique_ptr<Obstacle>> & getObstacles();
    
    GameObject& getForegroundLeft();
    
    GameObject& getForegroundRight();
    
    PlaneDynamicGameObject & getPlane();
    
    Environment_Type getEnvironmentType();
    
    int getScore();
    
    bool isGameOver();
    
private:
    std::vector<std::unique_ptr<Obstacle>> m_obstacles;
    std::unique_ptr<PlaneDynamicGameObject> m_plane;
    std::unique_ptr<GameObject> m_foregroundLeft;
    std::unique_ptr<GameObject> m_foregroundRight;
    Environment_Type m_environmentType;
    int m_iScore;
};

#endif /* defined(__tappyplane__World__) */