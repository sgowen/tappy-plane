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

#include <memory>
#include <vector>

#include <3ds.h>

class Rectangle;

struct QUAD
{
    float x1, y1, x2, y2, x3, y3, x4, y4; // Vertices
    float u1, v1, u2, v2, u3, v3, u4, v4; // Texture Coordinates
    float r, g, b, a; // Vertex color
};

class DSSpriteBatcher : public SpriteBatcher
{
public:
    DSSpriteBatcher(gfxScreen_t screen, int screenWidth, int screenHeight);
    
    virtual void beginBatch();
    
    virtual void endBatch(TextureWrapper &textureWrapper);
    
    virtual void endBatch(TextureWrapper &textureWrapper, GpuProgramWrapper &gpuProgramWrapper);
    
    virtual void drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr);
    
    virtual void drawSprite(float x, float y, float width, float height, float angle, Color &color, TextureRegion tr);
    
protected:
    virtual void drawSprite(float x, float y, float width, float height, TextureRegion tr);
    
    virtual void drawSprite(float x, float y, float width, float height, Color &color, TextureRegion tr);
    
private:
    std::unique_ptr<GpuProgramWrapper> m_textureProgram;
    std::vector<QUAD> m_quads;
    gfxScreen_t m_screen;
    int m_iScreenWidth;
    int m_iScreenHeight;
    
    void addQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4, float r, float g, float b, float a);
};

#endif /* defined(__gowengamedev__DSSpriteBatcher__) */