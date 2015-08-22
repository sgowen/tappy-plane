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
#include "OverlapTester.h"

#define DS_BOTTOM_W 318.0f
#define DS_BOTTOM_H 238.0f
#define DS_BOTTOM_PADDING 1

DSSpriteBatcher::DSSpriteBatcher()
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
        // Please note that the 3DS screens are sideways (thus 240x400 and 240x320)
        u8* fb = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);

        int left, top, right, bottom, x1, y1, x2, y2, x3, y3, x4, y4;

        for (std::vector<QUAD>::iterator itr = m_quads.begin(); itr != m_quads.end(); ++itr)
        {
            QUAD quad = *itr;

            x1 = (int) (quad.X1 / SCREEN_WIDTH * DS_BOTTOM_W + DS_BOTTOM_PADDING);
            y1 = (int) (quad.Y1 / SCREEN_HEIGHT * DS_BOTTOM_H + DS_BOTTOM_PADDING);

            x2 = (int) (quad.X2 / SCREEN_WIDTH * DS_BOTTOM_W + DS_BOTTOM_PADDING);
            y2 = (int) (quad.Y2 / SCREEN_HEIGHT * DS_BOTTOM_H + DS_BOTTOM_PADDING);

            x3 = (int) (quad.X3 / SCREEN_WIDTH * DS_BOTTOM_W + DS_BOTTOM_PADDING);
            y3 = (int) (quad.Y3 / SCREEN_HEIGHT * DS_BOTTOM_H + DS_BOTTOM_PADDING);

            x4 = (int) (quad.X4 / SCREEN_WIDTH * DS_BOTTOM_W + DS_BOTTOM_PADDING);
            y4 = (int) (quad.Y4 / SCREEN_HEIGHT * DS_BOTTOM_H + DS_BOTTOM_PADDING);

            left = x1;
            left = x2 < left ? x2 : left;
            left = x3 < left ? x3 : left;
            left = x4 < left ? x4 : left;

            right = x1;
            right = x2 > right ? x2 : right;
            right = x3 > right ? x3 : right;
            right = x4 > right ? x4 : right;

            bottom = y1;
            bottom = y2 < bottom ? y2 : bottom;
            bottom = y3 < bottom ? y3 : bottom;
            bottom = y4 < bottom ? y4 : bottom;

            top = y1;
            top = y2 > top ? y2 : top;
            top = y3 > top ? y3 : top;
            top = y4 > top ? y4 : top;

            for (int x = left; x < right; x++)
            {
                if (x >= DS_BOTTOM_PADDING && x <= (DS_BOTTOM_W + DS_BOTTOM_PADDING))
                {
                    for (int y = bottom; y < top; y++)
                    {
                        if (y >= DS_BOTTOM_PADDING && y <= (DS_BOTTOM_H + DS_BOTTOM_PADDING))
                        {
                            setPixel(fb, x, y, (int)(quad.R * 255), (int)(quad.G * 255), (int)(quad.B * 255));
                        }
                    }
                }
            }
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

        addQuad(x1, y1, x4, y4, x3, y3, x2, y2, 1, 1, 1);
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

        addQuad(x1, y1, x4, y4, x3, y3, x2, y2, color.red, color.green, color.blue);
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

    addQuad(x1, y1, x1, y2, x2, y2, x2, y1, 1, 1, 1);
}

void DSSpriteBatcher::drawSprite(float x, float y, float width, float height, Color &color, TextureRegion tr)
{
    float halfWidth = width / 2;
    float halfHeight = height / 2;
    float x1 = x - halfWidth;
    float y1 = y - halfHeight;
    float x2 = x + halfWidth;
    float y2 = y + halfHeight;

    addQuad(x1, y1, x1, y2, x2, y2, x2, y1, color.red, color.green, color.blue);
}

#pragma mark private

void DSSpriteBatcher::addQuad(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b)
{
    QUAD q = {x1, y1, x2, y2, x3, y3, x4, y4, r, g, b};
    m_quads.push_back(q);
}

void DSSpriteBatcher::setPixel(uint8_t *framebuffer, int x, int y, int red, int green, int blue)
{
    framebuffer[3 * (y + x * 240)] = blue;
    framebuffer[3 * (y + x * 240) + 1] = green;
    framebuffer[3 * (y + x * 240) + 2] = red;
}