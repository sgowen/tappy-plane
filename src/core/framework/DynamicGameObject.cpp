//
//  DynamicGameObject.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "DynamicGameObject.h"
#include "Vector2D.h"
#include "Rectangle.h"

DynamicGameObject::DynamicGameObject(float x, float y, float width, float height, float angle) : GameObject(x, y, width, height, angle)
{
    m_velocity = std::unique_ptr<Vector2D>(new Vector2D());
    m_acceleration = std::unique_ptr<Vector2D>(new Vector2D());
}

const Vector2D& DynamicGameObject::getVelocity()
{
    return *m_velocity;
}

const Vector2D& DynamicGameObject::getAcceleration()
{
    return *m_acceleration;
}
