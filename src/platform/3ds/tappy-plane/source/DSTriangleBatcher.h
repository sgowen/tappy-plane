//
//  OpenGLESTriangleBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__OpenGLESTriangleBatcher__
#define __gowengamedev__OpenGLESTriangleBatcher__

#include "TriangleBatcher.h"
#include "OverlapTester.h"

#include <vector>

#include <3ds.h>

struct TRIANGLE
{
    float x1, y1, x2, y2, x3, y3;
};

class DSTriangleBatcher : public TriangleBatcher
{
public:
    DSTriangleBatcher(bool isFill);

    virtual void beginBatch();

    virtual void endBatch();

    virtual void renderTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color &color);

private:
    std::vector<TRIANGLE> m_triangles;
    
    void setPixel(uint8_t *framebuffer, int x, int y, int red, int green, int blue);
};

#endif /* defined(__gowengamedev__OpenGLESTriangleBatcher__) */
