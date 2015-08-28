//
//  DSRectangleBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/25/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "DSRectangleBatcher.h"
#include "macros.h"
#include "Rectangle.h"
#include "Vector2D.h"
#include "GameConstants.h"
#include "DummyGpuProgramWrapper.h"

#include <sf2d.h>

#define RECT_LINE_THICKNESS GAME_WIDTH / 800.0f

DSRectangleBatcher::DSRectangleBatcher(gfxScreen_t screen, int screenWidth, int screenHeight, bool isFill) : RectangleBatcher(isFill), m_screen(screen), m_iScreenWidth(screenWidth), m_iScreenHeight(screenHeight)
{
    m_iNumRectangles = 0;
}

void DSRectangleBatcher::beginBatch()
{
    m_rects.clear();
    m_iNumRectangles = 0;
}

void DSRectangleBatcher::endBatch()
{
    endBatch(*DummyGpuProgramWrapper::getInstance());
}

void DSRectangleBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
    if (m_iNumRectangles > 0)
    {
        if (m_isFill)
        {
            for (std::vector<RECT>::iterator itr = m_rects.begin(); itr != m_rects.end(); ++itr)
            {
                RECT r = *itr;

                float width = r.x2 - r.x1;
                float height = r.y2 - r.y1;
                float x = r.x1 + width / 2;
                float y = r.y1 + height / 2;

                sf2d_draw_rectangle(x, y, width, height, RGBA8((int) (r.r * 255), (int) (r.g * 255), (int) (r.b * 255), (int) (r.a * 255)));
            }
        }
        else
        {
            for (std::vector<RECT>::iterator itr = m_rects.begin(); itr != m_rects.end(); ++itr)
            {
                RECT r = *itr;

                sf2d_draw_line(r.x1, r.y1, r.x2, r.y1, RECT_LINE_THICKNESS, RGBA8((int) (r.r * 255), (int) (r.g * 255), (int) (r.b * 255), (int) (r.a * 255)));
                sf2d_draw_line(r.x2, r.y1, r.x2, r.y2, RECT_LINE_THICKNESS, RGBA8((int) (r.r * 255), (int) (r.g * 255), (int) (r.b * 255), (int) (r.a * 255)));
                sf2d_draw_line(r.x2, r.y2, r.x1, r.y2, RECT_LINE_THICKNESS, RGBA8((int) (r.r * 255), (int) (r.g * 255), (int) (r.b * 255), (int) (r.a * 255)));
                sf2d_draw_line(r.x1, r.y2, r.x1, r.y1, RECT_LINE_THICKNESS, RGBA8((int) (r.r * 255), (int) (r.g * 255), (int) (r.b * 255), (int) (r.a * 255)));
            }
        }
    }
}

void DSRectangleBatcher::renderRectangle(float x1, float y1, float x2, float y2, Color &c)
{
    RECT r = {x1, GAME_HEIGHT - y1, x2, GAME_HEIGHT - y2, c.red, c.green, c.blue, c.alpha};
    m_rects.push_back(r);

    m_iNumRectangles++;
}