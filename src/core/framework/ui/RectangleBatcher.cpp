//
//  RectangleBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 9/25/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "RectangleBatcher.h"
#include "Rectangle.h"
#include "Vector2D.h"

RectangleBatcher::RectangleBatcher(bool isFill)
{
    m_iNumRectangles = 0;
    m_isFill = isFill;
}

void RectangleBatcher::renderRectangle(Rectangle &rectangle, Color &color)
{
    float x1 = rectangle.getLowerLeft().getX();
    float y1 = rectangle.getLowerLeft().getY();
    float x2 = x1 + rectangle.getWidth();
    float y2 = y1 + rectangle.getHeight();
    
    renderRectangle(x1, y1, x2, y2, color);
}
