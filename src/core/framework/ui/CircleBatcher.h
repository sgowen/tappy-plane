//
//  CircleBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__CircleBatcher__
#define __gowengamedev__CircleBatcher__

#include "Color.h"

class Circle;

class CircleBatcher
{
public:
    CircleBatcher();
    
    virtual void renderCircle(Circle &circle, Color &color) = 0;
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &color) = 0;
};

#endif /* defined(__gowengamedev__CircleBatcher__) */
