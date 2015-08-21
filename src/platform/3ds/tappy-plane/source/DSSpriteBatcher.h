//
//  DSSpriteBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__DSSpriteBatcher__
#define __gowengamedev__DSSpriteBatcher__

#include "SpriteBatcher.h"

#include <vector>

#include <3ds.h>

class Rectangle;

struct QUAD
{
    float X1, Y1; // vertex position
    float X2, Y2; // vertex position
    float X3, Y3; // vertex position
    float X4, Y4; // vertex position
    float R, G, B; // vertex color
};

class DSSpriteBatcher : public SpriteBatcher
{
public:
    DSSpriteBatcher();
    
    virtual void beginBatch();
    
    virtual void endBatchWithTexture(TextureWrapper &textureWrapper);
    
    virtual void drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr);
    
    virtual void drawSprite(float x, float y, float width, float height, float angle, Color &color, TextureRegion tr);
    
protected:
    virtual void drawSprite(float x, float y, float width, float height, TextureRegion tr);
    
    virtual void drawSprite(float x, float y, float width, float height, Color &color, TextureRegion tr);
    
private:
    std::vector<QUAD> m_quads;
    
    void addQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b);
    
    void setPixel(uint8_t *framebuffer, int x, int y, int red, int green, int blue);
};

#endif /* defined(__gowengamedev__DSSpriteBatcher__) */