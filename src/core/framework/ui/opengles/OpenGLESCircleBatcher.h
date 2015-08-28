//
//  OpenGLESCircleBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__OpenGLESCircleBatcher__
#define __gowengamedev__OpenGLESCircleBatcher__

#include "CircleBatcher.h"

class OpenGLESCircleBatcher : public CircleBatcher
{
public:
    OpenGLESCircleBatcher();
    
    virtual void renderCircle(Circle &circle, Color &c);
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &c);
    
    virtual void renderCircle(Circle &circle, Color &c, GpuProgramWrapper &gpuProgramWrapper);
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &c, GpuProgramWrapper &gpuProgramWrapper);
    
protected:
    virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper);
};

#endif /* defined(__gowengamedev__OpenGLESCircleBatcher__) */
