//
//  Rectangle.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "Rectangle.h"
#include "Vector2D.h"

Rectangle::Rectangle(float x, float y, float width, float height, float angle)
{
    m_LowerLeft = new Vector2D(x, y);
    m_fWidth = width;
    m_fHeight = height;
    m_fAngle = angle;
}

Rectangle::~Rectangle()
{
    delete m_LowerLeft;
    m_LowerLeft = 0;
}

Vector2D& Rectangle::getLowerLeft()
{
    return *m_LowerLeft;
}

const float Rectangle::getWidth() const
{
    return m_fWidth;
}

const void Rectangle::setWidth(float width)
{
    m_fWidth = width;
}

const float Rectangle::getHeight() const
{
    return m_fHeight;
}

const void Rectangle::setHeight(float height)
{
    m_fHeight = height;
}

const float Rectangle::getAngle() const
{
    return m_fAngle;
}

const void Rectangle::setAngle(float angle)
{
    m_fAngle = angle;
}