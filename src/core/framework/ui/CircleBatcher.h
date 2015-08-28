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
class GpuProgramWrapper;

class CircleBatcher
{
public:
    CircleBatcher();
    
    virtual void renderCircle(Circle &circle, Color &c) = 0;
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &c) = 0;
    
    virtual void renderCircle(Circle &circle, Color &c, GpuProgramWrapper &gpuProgramWrapper) = 0;
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &c, GpuProgramWrapper &gpuProgramWrapper) = 0;
    
protected:
    int m_iNumPoints;
    
    virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper) = 0;
};

#endif /* defined(__gowengamedev__CircleBatcher__) */
