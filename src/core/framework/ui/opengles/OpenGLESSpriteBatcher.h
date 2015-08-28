//
//  OpenGLESSpriteBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__OpenGLESSpriteBatcher__
#define __gowengamedev__OpenGLESSpriteBatcher__

#include "SpriteBatcher.h"

class OpenGLESSpriteBatcher : public SpriteBatcher
{
public:
    OpenGLESSpriteBatcher();
    
    virtual void beginBatch();
    
    virtual void endBatch(TextureWrapper &textureWrapper);
    
    virtual void endBatch(TextureWrapper &textureWrapper, GpuProgramWrapper &gpuProgramWrapper);
    
    virtual void drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr);
    
    virtual void drawSprite(float x, float y, float width, float height, float angle, Color &c, TextureRegion tr);
    
protected:
    virtual void drawSprite(float x, float y, float width, float height, TextureRegion tr);
    
    virtual void drawSprite(float x, float y, float width, float height, Color &c, TextureRegion tr);
};

#endif /* defined(__gowengamedev__OpenGLESSpriteBatcher__) */