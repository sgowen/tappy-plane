//
//  GameObject.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "GameObject.h"
#include "Rectangle.h"
#include "Vector2D.h"

GameObject::GameObject(float x, float y, float width, float height, float angle)
{
    m_position = std::unique_ptr<Vector2D>(new Vector2D(x, y));
    m_bounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, y - height / 2, width, height));
    
    m_fWidth = width;
    m_fHeight = height;
    m_fAngle = angle;
}

void GameObject::resetBounds(float width, float height)
{
    Vector2D &lowerLeft = m_bounds->getLowerLeft();
    lowerLeft.set(m_position->getX() - width / 2, m_position->getY() - height / 2);
    m_bounds->setWidth(width);
    m_bounds->setHeight(height);
}

void GameObject::updateBounds()
{
    Vector2D &lowerLeft = m_bounds->getLowerLeft();
    lowerLeft.set(m_position->getX() - m_bounds->getWidth() / 2, m_position->getY() - m_bounds->getHeight() / 2);
}

Vector2D& GameObject::getPosition()
{
    return *m_position;
}

Rectangle& GameObject::getBounds()
{
    return *m_bounds;
}

const float& GameObject::getWidth()
{
    return m_fWidth;
}

const float& GameObject::getHeight()
{
    return m_fHeight;
}

float GameObject::getAngle()
{
    return m_fAngle;
}
