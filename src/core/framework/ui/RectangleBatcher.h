//
//  RectangleBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 9/25/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__RectangleBatcher__
#define __gowengamedev__RectangleBatcher__

#include "Color.h"

class Rectangle;

class RectangleBatcher
{
public:
    RectangleBatcher(bool isFill);
    
    virtual void beginBatch() = 0;
    
    virtual void endBatch() = 0;
    
    void renderRectangle(Rectangle &rectangle, Color &color);
    
    virtual void renderRectangle(float leftX, float bottomY, float rightX, float topY, Color &color) = 0;
    
protected:
    int m_iNumRectangles;
    bool m_isFill;
};

#endif /* defined(__gowengamedev__RectangleBatcher__) */
