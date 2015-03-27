//
//  Circle.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/6/13.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "Circle.h"
#include "Vector2D.h"

Circle::Circle(float x, float y, float radius)
{
    m_center = std::unique_ptr<Vector2D>(new Vector2D(x, y));
    m_fRadius = radius;
}

Vector2D& Circle::getCenter() const
{
    return *m_center;
}