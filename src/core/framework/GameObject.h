//
//  GameObject.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef GameObject_H
#define GameObject_H

#include <memory>

class Rectangle;
class Vector2D;

class GameObject
{
protected:
    std::unique_ptr<Vector2D> m_position;
    std::unique_ptr<Rectangle> m_bounds;
    float m_fWidth;
    float m_fHeight;
    float m_fAngle;

public:
    GameObject(float x, float y, float width, float height, float angle);

    virtual void resetBounds(float width, float height);

    virtual void updateBounds();

    Vector2D& getPosition();

    Rectangle& getBounds();

    const float& getWidth();

    const float& getHeight();
    
    virtual float getAngle();
};

#endif /* GameObject_H */
