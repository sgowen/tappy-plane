//
//  PhysicalEntity.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "PhysicalEntity.h"
#include "Rectangle.h"
#include "Vector2D.h"

PhysicalEntity::PhysicalEntity(float x, float y, float width, float height, float angle) : Entity()
{
    m_position = std::unique_ptr<Vector2D>(new Vector2D(x, y));
    m_velocity = std::unique_ptr<Vector2D>(new Vector2D());
    m_acceleration = std::unique_ptr<Vector2D>(new Vector2D());
    m_bounds = std::unique_ptr<Rectangle>(new Rectangle(x - width / 2, y - height / 2, width, height));

    m_fWidth = width;
    m_fHeight = height;
    m_fAngle = angle;
}

void PhysicalEntity::resetBounds(float width, float height)
{
    Vector2D &lowerLeft = m_bounds->getLowerLeft();
    lowerLeft.set(m_position->getX() - width / 2, m_position->getY() - height / 2);
    m_bounds->setWidth(width);
    m_bounds->setHeight(height);
}

void PhysicalEntity::updateBounds()
{
    Vector2D &lowerLeft = m_bounds->getLowerLeft();
    lowerLeft.set(m_position->getX() - m_bounds->getWidth() / 2, m_position->getY() - m_bounds->getHeight() / 2);
}

Vector2D& PhysicalEntity::getPosition()
{
    return *m_position;
}

Vector2D& PhysicalEntity::getVelocity()
{
    return *m_velocity;
}

Vector2D& PhysicalEntity::getAcceleration()
{
    return *m_acceleration;
}

Rectangle& PhysicalEntity::getBounds()
{
    return *m_bounds;
}

const float& PhysicalEntity::getWidth()
{
    return m_fWidth;
}

const float& PhysicalEntity::getHeight()
{
    return m_fHeight;
}

float PhysicalEntity::getAngle()
{
    return m_fAngle;
}