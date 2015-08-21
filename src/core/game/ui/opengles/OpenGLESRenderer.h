//
//  OpenGLESRenderer.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__OpenGLESRenderer__
#define __tappyplane__OpenGLESRenderer__

#include "Renderer.h"

class OpenGLESRenderer : public Renderer
{
public:
    OpenGLESRenderer();
    
    virtual void clearScreenWithColor(float r, float g, float b, float a);
    
    virtual void beginFrame();
    
    virtual void endFrame();
    
    virtual void cleanUp();
};

#endif /* defined(__tappyplane__OpenGLESRenderer__) */