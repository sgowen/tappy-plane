//
//  Line.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/20/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "Line.h"

Line::Line(float x1, float y1, float x2, float y2)
{
    m_origin = std::unique_ptr<Vector2D>(new Vector2D(x1, y1));
    m_end = std::unique_ptr<Vector2D>(new Vector2D(x2, y2));
}

Vector2D& Line::getOrigin()
{
    return *m_origin;
}

Vector2D& Line::getEnd()
{
    return *m_end;
}