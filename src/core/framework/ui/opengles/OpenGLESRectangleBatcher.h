//
//  OpenGLESRectangleBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 7/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__OpenGLESRectangleBatcher__
#define __gowengamedev__OpenGLESRectangleBatcher__

#include "RectangleBatcher.h"

class OpenGLESRectangleBatcher : public RectangleBatcher
{
public:
    OpenGLESRectangleBatcher(bool isFill);
    
    virtual void beginBatch();
    
    virtual void endBatch();
    
    virtual void renderRectangle(float x1, float y1, float x2, float y2, Color &color);
};

#endif /* defined(__gowengamedev__OpenGLESRectangleBatcher__) */
