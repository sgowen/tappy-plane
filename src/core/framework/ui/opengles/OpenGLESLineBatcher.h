//
//  OpenGLESLineBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__OpenGLESLineBatcher__
#define __gowengamedev__OpenGLESLineBatcher__

#include "LineBatcher.h"

class OpenGLESLineBatcher : public LineBatcher
{
public:
    OpenGLESLineBatcher();
    
    virtual void beginBatch();
    
    virtual void endBatch();
    
    virtual void renderLine(float originX, float originY, float endX, float endY, Color &color);
};

#endif /* defined(__gowengamedev__OpenGLESLineBatcher__) */
