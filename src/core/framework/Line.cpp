//
//  Line.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "Line.h"
#include "Vector2D.h"

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
