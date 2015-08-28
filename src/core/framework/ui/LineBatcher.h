//
//  LineBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__LineBatcher__
#define __gowengamedev__LineBatcher__

#include "Color.h"

class Line;
class GpuProgramWrapper;

class LineBatcher
{
public:
    LineBatcher();
    
    virtual void beginBatch() = 0;
    
    virtual void endBatch() = 0;
    
    virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper) = 0;
    
    void renderLine(Line &line, Color &c);
    
    virtual void renderLine(float originX, float originY, float endX, float endY, Color &c) = 0;
    
protected:
    int m_iNumLines;
};

#endif /* defined(__gowengamedev__LineBatcher__) */
