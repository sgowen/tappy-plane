//
//  DSLineBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/25/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__DSLineBatcher__
#define __gowengamedev__DSLineBatcher__

#include "LineBatcher.h"

#include <vector>

#include <3ds.h>

struct LINE
{
    float oX, oY, eX, eY; // Vertices
    float r, g, b, a; // Color for Vertices
};

class DSLineBatcher : public LineBatcher
{
public:
    DSLineBatcher(gfxScreen_t screen, int screenWidth, int screenHeight);

    virtual void beginBatch();

    virtual void endBatch();

    virtual void renderLine(float originX, float originY, float endX, float endY, Color &color);

private:
    std::vector<LINE> m_lines;
    gfxScreen_t m_screen;
    int m_iScreenWidth;
    int m_iScreenHeight;
};

#endif /* defined(__gowengamedev__DSLineBatcher__) */
