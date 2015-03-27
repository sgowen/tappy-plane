//
//  LineBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "LineBatcher.h"
#include "Line.h"
#include "Vector2D.h"

LineBatcher::LineBatcher()
{
    m_iNumLines = 0;
}

void LineBatcher::renderLine(Line &line, Color &color)
{
    float oX = line.getOrigin().getX();
    float oY = line.getOrigin().getY();
    float eX = line.getEnd().getX();
    float eY = line.getEnd().getY();
    
    renderLine(oX, oY, eX, eY, color);
}
