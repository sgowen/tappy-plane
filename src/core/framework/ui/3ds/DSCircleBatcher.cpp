//
//  DSCircleBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/25/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#define DEGREE_SPACING 36

#include "DSCircleBatcher.h"
#include "macros.h"
#include "Circle.h"
#include "Vector2D.h"
#include "math.h"
#include "GameConstants.h"
#include "DummyGpuProgramWrapper.h"

DSCircleBatcher::DSCircleBatcher(gfxScreen_t screen, int screenWidth, int screenHeight) : CircleBatcher(), m_screen(screen), m_iScreenWidth(screenWidth), m_iScreenHeight(screenHeight), m_iNumPointsOnCircle(0)
{
    // Empty
}

void DSCircleBatcher::renderCircle(Circle &circle, Color &c)
{
    renderCircle(circle, c, *DummyGpuProgramWrapper::getInstance());
}

void DSCircleBatcher::renderPartialCircle(Circle &circle, int arcDegrees, Color &c)
{
    renderPartialCircle(circle, arcDegrees, c, *DummyGpuProgramWrapper::getInstance());
}

void DSCircleBatcher::renderCircle(Circle &circle, Color &c, GpuProgramWrapper &gpuProgramWrapper)
{
    renderCircle(circle.getCenter().getX(), circle.getCenter().getY(), circle.m_fRadius, c, gpuProgramWrapper);
}

void DSCircleBatcher::renderPartialCircle(Circle &circle, int arcDegrees, Color &c, GpuProgramWrapper &gpuProgramWrapper)
{
    // This method should display clockwise depleting circle, but I couldn't figure out how to do it, so...
    float radius = circle.m_fRadius;
    radius *= (1 - (((float) arcDegrees) / 360.0f));

    renderCircle(circle.getCenter().getX(), circle.getCenter().getY(), radius, c, gpuProgramWrapper);
}

void DSCircleBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
    sf2d_draw_batch_circle(&m_vertices[0], m_iNumPointsOnCircle);
}

void DSCircleBatcher::renderCircle(float x, float y, float radius, Color &c, GpuProgramWrapper &gpuProgramWrapper)
{
    m_iNumPointsOnCircle = 0;
    m_vertices.clear();

    addVertex(x, y, c.red, c.green, c.blue, c.alpha);

    for (int i = 0; i < 360; i += DEGREE_SPACING)
    {
        float rad = DEGREES_TO_RADIANS(i);
        float cos = cosf(rad);
        float sin = sinf(rad);

        addVertex(cos * radius + x, sin * radius + y, c.red, c.green, c.blue, c.alpha);
    }

    float rad = DEGREES_TO_RADIANS(0);
    float cos = cosf(rad);
    float sin = sinf(rad);

    addVertex(cos * radius + x, sin * radius + y, c.red, c.green, c.blue, c.alpha);

    endBatch(gpuProgramWrapper);
}

void DSCircleBatcher::addVertex(float x, float y, float r, float g, float b, float a)
{
    sf2d_vector_3f vertex = (sf2d_vector_3f){x, GAME_HEIGHT - y, SF2D_DEFAULT_DEPTH};
    sf2d_vector_4f color = (sf2d_vector_4f){r, g, b, a};
    sf2d_vertex_pos_col v = (sf2d_vertex_pos_col){vertex, color};
    m_vertices.push_back(v);

    m_iNumPointsOnCircle++;
}