//
//  SpriteBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 9/25/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__SpriteBatcher__
#define __gowengamedev__SpriteBatcher__

#include "Color.h"
#include "TextureWrapper.h"

class TextureRegion;
class GpuProgramWrapper;

class SpriteBatcher
{
public:
    SpriteBatcher();

    virtual void beginBatch() = 0;

    virtual void endBatch(TextureWrapper &textureWrapper) = 0;

    virtual void endBatch(TextureWrapper &textureWrapper, GpuProgramWrapper &gpuProgramWrapper) = 0;

    virtual void drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr) = 0;

    virtual void drawSprite(float x, float y, float width, float height, float angle, Color &c, TextureRegion tr) = 0;

protected:
    int m_iNumSprites;

    virtual void drawSprite(float x, float y, float width, float height, TextureRegion tr) = 0;

    virtual void drawSprite(float x, float y, float width, float height, Color &c, TextureRegion tr) = 0;
};

#endif /* defined(__gowengamedev__SpriteBatcher__) */