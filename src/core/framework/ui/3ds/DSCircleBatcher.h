//
//  DSCircleBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/25/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__DSCircleBatcher__
#define __gowengamedev__DSCircleBatcher__

#include "CircleBatcher.h"

#include <vector>

#include <3ds.h>

#include <sf2d.h>

class DSCircleBatcher : public CircleBatcher
{
public:
    DSCircleBatcher(gfxScreen_t screen, int screenWidth, int screenHeight);
    
    virtual void renderCircle(Circle &circle, Color &c);
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &c);
    
    virtual void renderCircle(Circle &circle, Color &c, GpuProgramWrapper &gpuProgramWrapper);
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &c, GpuProgramWrapper &gpuProgramWrapper);
    
protected:
    virtual void endBatch(GpuProgramWrapper &gpuProgramWrapper);
    
private:
    std::vector<sf2d_vertex_pos_col> m_vertices;
    gfxScreen_t m_screen;
    int m_iScreenWidth;
    int m_iScreenHeight;
    int m_iNumPointsOnCircle;
    
    void renderCircle(float x, float y, float radius, Color &c, GpuProgramWrapper &gpuProgramWrapper);
    
    void addVertex(float x, float y, float r, float g, float b, float a);
};

#endif /* defined(__gowengamedev__DSCircleBatcher__) */
