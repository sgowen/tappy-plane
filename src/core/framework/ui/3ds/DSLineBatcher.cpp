//
//  DSLineBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/25/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "DSLineBatcher.h"
#include "macros.h"
#include "Line.h"
#include "Vector2D.h"
#include "GameConstants.h"
#include "DummyGpuProgramWrapper.h"

#include <sf2d.h>

#define LINE_THICKNESS GAME_WIDTH / 1000.0f

DSLineBatcher::DSLineBatcher(gfxScreen_t screen, int screenWidth, int screenHeight) : m_screen(screen), m_iScreenWidth(screenWidth), m_iScreenHeight(screenHeight)
{
    m_iNumLines = 0;
}

void DSLineBatcher::beginBatch()
{
    m_lines.clear();
    m_iNumLines = 0;
}

void DSLineBatcher::endBatch()
{
    endBatch(*DummyGpuProgramWrapper::getInstance());
}

void DSLineBatcher::endBatch(GpuProgramWrapper &gpuProgramWrapper)
{
    if (m_iNumLines > 0)
    {
        for (std::vector<LINE>::iterator itr = m_lines.begin(); itr != m_lines.end(); ++itr)
        {
            LINE l = *itr;

            sf2d_draw_line(l.oX, l.oY, l.eX, l.eY, LINE_THICKNESS, RGBA8((int) (l.r * 255), (int) (l.g * 255), (int) (l.b * 255), (int) (l.a * 255)));
        }
    }
}

void DSLineBatcher::renderLine(float originX, float originY, float endX, float endY, Color &c)
{
    LINE l = {originX, GAME_HEIGHT - originY, endX, GAME_HEIGHT - endY, c.red, c.green, c.blue, c.alpha};
    m_lines.push_back(l);

    m_iNumLines++;
}