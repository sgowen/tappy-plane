//
//  Vector2D.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "macros.h"
#include "Vector2D.h"

#include <math.h>

Vector2D::Vector2D(const Vector2D &cSource)
{
    m_fX = cSource.getX();
    m_fY = cSource.getY();
}

Vector2D Vector2D::set(const Vector2D &other)
{
    m_fX = other.getX();
    m_fY = other.getY();
    
    return *this;
}

Vector2D Vector2D::set(float x, float y)
{
    m_fX = x;
    m_fY = y;
    
    return *this;
}

Vector2D Vector2D::setX(float x)
{
	m_fX = x;
    
    return *this;
}

Vector2D Vector2D::setY(float y)
{
	m_fY = y;
    
    return *this;
}

Vector2D Vector2D::cpy()
{
	return Vector2D(m_fX, m_fY);
}

void Vector2D::operator+= (const Vector2D &other)
{
    add(other.getX(), other.getY());
}

Vector2D Vector2D::add(float x, float y)
{
    m_fX += x;
    m_fY += y;
    
    return *this;
}

void Vector2D::operator-= (const Vector2D &other)
{
    sub(other.getX(), other.getY());
}

Vector2D Vector2D::sub(float x, float y)
{
    m_fX -= x;
    m_fY -= y;
    
    return *this;
}

Vector2D Vector2D::operator*= (float scalar)
{
    return mul(scalar);
}

Vector2D Vector2D::mul(float scalar)
{
    m_fX *= scalar;
    m_fY *= scalar;
    
    return *this;
}

float Vector2D::len()
{
    return sqrtf(m_fX * m_fX + m_fY * m_fY);
}

Vector2D Vector2D::nor()
{
    float l = len();
    
    if (l != 0)
    {
        m_fX /= l;
        m_fY /= l;
    }
    
    return *this;
}

float Vector2D::angle()
{
    float radians = atan2f(m_fY, m_fX);
    float angle = RADIANS_TO_DEGREES(radians);
    
    if (angle < 0)
    {
        angle += 360;
    }
    
    return angle;
}

Vector2D Vector2D::rotate(float angle)
{
    float rad = DEGREES_TO_RADIANS(angle);
    float cos = cosf(rad);
    float sin = sinf(rad);
    
    float newX = m_fX * cos - m_fY * sin;
    float newY = m_fX * sin + m_fY * cos;
    
    m_fX = newX;
    m_fY = newY;
    
    return *this;
}

float Vector2D::dist(const Vector2D &other) const
{
    return dist(other.getX(), other.getY());
}

float Vector2D::dist(float x, float y) const
{
    return sqrtf(distSquared(x, y));
}

float Vector2D::distSquared(const Vector2D &other) const
{
    return distSquared(other.getX(), other.getY());
}

float Vector2D::distSquared(float x, float y) const
{
    float distX = m_fX - x;
    float distY = m_fY - y;
    
    return distX * distX + distY * distY;
}

float Vector2D::getX() const
{
    return m_fX;
}

float Vector2D::getY() const
{
    return m_fY;
}
