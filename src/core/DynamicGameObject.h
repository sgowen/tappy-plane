//
//  DynamicGameObject.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef DynamicGameObject_H
#define DynamicGameObject_H

#include "GameObject.h"

class Vector2D;

class DynamicGameObject : public GameObject
{
protected:
	std::unique_ptr<Vector2D> m_velocity;
	std::unique_ptr<Vector2D> m_acceleration;
    
public:
    DynamicGameObject(float x, float y, float width, float height, float angle);
    
    const Vector2D& getVelocity();
    
    const Vector2D& getAcceleration();
};

#endif /* DynamicGameObject_H */