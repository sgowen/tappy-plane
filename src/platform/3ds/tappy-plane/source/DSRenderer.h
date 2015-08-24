//
//  DSRenderer.h
//  tappyplane
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__DSRenderer__
#define __tappyplane__DSRenderer__

#include "Renderer.h"

#include <3ds.h>

class TriangleBatcher;

class DSRenderer : public Renderer
{
public:
    DSRenderer(gfxScreen_t screen, int screenWidth, int screenHeight);

    virtual void clearScreenWithColor(float r, float g, float b, float a);

    virtual void beginFrame();

    virtual void endFrame();

    virtual void cleanUp();

    virtual void renderWorldBackground(World &world);

    virtual void renderWorldForeground(World &world, Glove &glove, float titleAlpha);
    
private:
    std::unique_ptr<TriangleBatcher> m_triangleBatcher;
};

#endif /* defined(__tappyplane__DSRenderer__) */
