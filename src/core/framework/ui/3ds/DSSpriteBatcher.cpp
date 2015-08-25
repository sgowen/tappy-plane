//
//  DSSpriteBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "macros.h"
#include "DSSpriteBatcher.h"
#include "GameConstants.h"
#include "TextureRegion.h"
#include "Rectangle.h"
#include "Vector2D.h"
#include "math.h"

#include <sf2d.h>

DSSpriteBatcher::DSSpriteBatcher(gfxScreen_t screen, int screenWidth, int screenHeight) : m_screen(screen), m_iScreenWidth(screenWidth), m_iScreenHeight(screenHeight)
{
    m_iNumSprites = 0;
}

void DSSpriteBatcher::beginBatch()
{
    m_quads.clear();
    m_iNumSprites = 0;
}

void DSSpriteBatcher::endBatchWithTexture(TextureWrapper &textureWrapper)
{
    if (m_iNumSprites > 0)
    {
        for (std::vector<QUAD>::iterator itr = m_quads.begin(); itr != m_quads.end(); ++itr)
        {
            QUAD quad = *itr;

            sf2d_draw_quad_uv(textureWrapper.texture, quad.x1, quad.y1, quad.x2, quad.y2, quad.x3, quad.y3, quad.x4, quad.y4, quad.u1, quad.v1, quad.u2, quad.v2, quad.u3, quad.v3, quad.u4, quad.v4, RGBA8((int)(quad.r * 255), (int)(quad.g * 255), (int)(quad.b * 255), (int)(quad.a * 255)), GPU_TEXTURE_MAG_FILTER(GPU_NEAREST) | GPU_TEXTURE_MIN_FILTER(GPU_NEAREST));
        }
    }
}

void DSSpriteBatcher::drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr)
{
    if (angle != 0)
    {
        float halfWidth = width / 2;
        float halfHeight = height / 2;

        float rad = DEGREES_TO_RADIANS(angle);
        float cos = cosf(rad);
        float sin = sinf(rad);

        float x1 = -halfWidth * cos - (-halfHeight) * sin;
        float y1 = -halfWidth * sin + (-halfHeight) * cos;

        float x2 = halfWidth * cos - (-halfHeight) * sin;
        float y2 = halfWidth * sin + (-halfHeight) * cos;

        float x3 = halfWidth * cos - halfHeight * sin;
        float y3 = halfWidth * sin + halfHeight * cos;

        float x4 = -halfWidth * cos - halfHeight * sin;
        float y4 = -halfWidth * sin + halfHeight * cos;

        x1 += x;
        y1 += y;

        x2 += x;
        y2 += y;

        x3 += x;
        y3 += y;

        x4 += x;
        y4 += y;

        addQuad(   x4,    y4,    x3,    y3,    x1,    y1,    x2,    y2,
                tr.u1, tr.v1, tr.u2, tr.v1, tr.u1, tr.v2, tr.u2, tr.v2, 1, 1, 1, 1);
    }
    else
    {
        drawSprite(x, y, width, height, tr);
    }

    m_iNumSprites++;
}

void DSSpriteBatcher::drawSprite(float x, float y, float width, float height, float angle, Color &color, TextureRegion tr)
{
    if (angle != 0)
    {
        float halfWidth = width / 2;
        float halfHeight = height / 2;

        float rad = DEGREES_TO_RADIANS(angle);
        float cos = cosf(rad);
        float sin = sinf(rad);

        float x1 = -halfWidth * cos - (-halfHeight) * sin;
        float y1 = -halfWidth * sin + (-halfHeight) * cos;

        float x2 = halfWidth * cos - (-halfHeight) * sin;
        float y2 = halfWidth * sin + (-halfHeight) * cos;

        float x3 = halfWidth * cos - halfHeight * sin;
        float y3 = halfWidth * sin + halfHeight * cos;

        float x4 = -halfWidth * cos - halfHeight * sin;
        float y4 = -halfWidth * sin + halfHeight * cos;

        x1 += x;
        y1 += y;

        x2 += x;
        y2 += y;

        x3 += x;
        y3 += y;

        x4 += x;
        y4 += y;

        addQuad(   x4,    y4,    x3,    y3,    x1,    y1,    x2,    y2,
                tr.u1, tr.v1, tr.u2, tr.v1, tr.u1, tr.v2, tr.u2, tr.v2, color.red, color.green, color.blue, color.alpha);
    }
    else
    {
        drawSprite(x, y, width, height, color, tr);
    }

    m_iNumSprites++;
}

#pragma private methods

void DSSpriteBatcher::drawSprite(float x, float y, float width, float height, TextureRegion tr)
{
    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float x1 = x - halfWidth;
    float y1 = y - halfHeight;
    float x2 = x + halfWidth;
    float y2 = y + halfHeight;

    addQuad(   x1,    y2,    x2,    y2,    x1,    y1,    x2,    y1,
            tr.u1, tr.v1, tr.u2, tr.v1, tr.u1, tr.v2, tr.u2, tr.v2, 1, 1, 1, 1);
}

void DSSpriteBatcher::drawSprite(float x, float y, float width, float height, Color &color, TextureRegion tr)
{
    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float x1 = x - halfWidth;
    float y1 = y - halfHeight;
    float x2 = x + halfWidth;
    float y2 = y + halfHeight;

    addQuad(   x1,    y2,    x2,    y2,    x1,    y1,    x2,    y1,
            tr.u1, tr.v1, tr.u2, tr.v1, tr.u1, tr.v2, tr.u2, tr.v2, color.red, color.green, color.blue, color.alpha);
}

#pragma mark private

void DSSpriteBatcher::addQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4, float r, float g, float b, float a)
{
    QUAD q = {x1, GAME_HEIGHT - y1, x2, GAME_HEIGHT - y2, x3, GAME_HEIGHT - y3, x4, GAME_HEIGHT - y4, u1, v1, u2, v2, u3, v3, u4, v4, r, g, b, a};
    m_quads.push_back(q);
}