//
//  PhysicalEntity.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef PhysicalEntity_H
#define PhysicalEntity_H

#include "Entity.h"

#include <memory>

class Rectangle;
class Vector2D;

class PhysicalEntity : public Entity
{
public:
    PhysicalEntity(float x, float y, float width, float height, float angle);

    virtual void resetBounds(float width, float height);

    virtual void updateBounds();

    Vector2D& getPosition();
    
    Vector2D& getVelocity();
    
    Vector2D& getAcceleration();

    Rectangle& getBounds();

    const float& getWidth();

    const float& getHeight();
    
    virtual float getAngle();
    
    virtual bool handleMessage(const Telegram& msg);
    
protected:
    std::unique_ptr<Vector2D> m_position;
    std::unique_ptr<Vector2D> m_velocity;
    std::unique_ptr<Vector2D> m_acceleration;
    std::unique_ptr<Rectangle> m_bounds;
    float m_fWidth;
    float m_fHeight;
    float m_fAngle;
};

#endif /* PhysicalEntity_H */
