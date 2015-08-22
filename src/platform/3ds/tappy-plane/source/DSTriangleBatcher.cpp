//
//  DSTriangleBatcher.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 7/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "DSTriangleBatcher.h"
#include "macros.h"
#include "Triangle.h"
#include "Vector2D.h"
#include "GameConstants.h"

#define DS_BOTTOM_W 318.0f
#define DS_BOTTOM_H 238.0f
#define DS_BOTTOM_PADDING 1

DSTriangleBatcher::DSTriangleBatcher(bool isFill) : TriangleBatcher(isFill)
{
    m_iNumTriangles = 0;
}

void DSTriangleBatcher::beginBatch()
{
    m_triangles.clear();
    m_iNumTriangles = 0;
}

void DSTriangleBatcher::endBatch()
{
    if (m_iNumTriangles > 0)
    {
        // Please note that the 3DS screens are sideways (thus 240x400 and 240x320)
        u8* fb = gfxGetFramebuffer(GFX_BOTTOM, GFX_LEFT, NULL, NULL);

        int left, top, right, bottom, x1, y1, x2, y2, x3, y3;

        for (std::vector<TRIANGLE>::iterator itr = m_triangles.begin(); itr != m_triangles.end(); ++itr)
        {
            TRIANGLE tri = *itr;

            x1 = (int) (tri.x1 / SCREEN_WIDTH * DS_BOTTOM_W + DS_BOTTOM_PADDING);
            y1 = (int) (tri.y1 / SCREEN_HEIGHT * DS_BOTTOM_H + DS_BOTTOM_PADDING);

            x2 = (int) (tri.x2 / SCREEN_WIDTH * DS_BOTTOM_W + DS_BOTTOM_PADDING);
            y2 = (int) (tri.y2 / SCREEN_HEIGHT * DS_BOTTOM_H + DS_BOTTOM_PADDING);

            x3 = (int) (tri.x3 / SCREEN_WIDTH * DS_BOTTOM_W + DS_BOTTOM_PADDING);
            y3 = (int) (tri.y3 / SCREEN_HEIGHT * DS_BOTTOM_H + DS_BOTTOM_PADDING);

            left = x1;
            left = x2 < left ? x2 : left;
            left = x3 < left ? x3 : left;

            right = x1;
            right = x2 > right ? x2 : right;
            right = x3 > right ? x3 : right;

            bottom = y1;
            bottom = y2 < bottom ? y2 : bottom;
            bottom = y3 < bottom ? y3 : bottom;

            top = y1;
            top = y2 > top ? y2 : top;
            top = y3 > top ? y3 : top;
            
            Point points[3] = {
                {x1, y1},
                {x2, y2},
                {x3, y3}
            };

            for (int x = left; x < right; x++)
            {
                if (x >= DS_BOTTOM_PADDING && x <= (DS_BOTTOM_W + DS_BOTTOM_PADDING))
                {
                    for (int y = bottom; y < top; y++)
                    {
                        if (y >= DS_BOTTOM_PADDING && y <= (DS_BOTTOM_H + DS_BOTTOM_PADDING))
                        {
                            Point p = {x, y};
                            if (OverlapTester::isInside(points, 3, p))
                            {
                                setPixel(fb, x, y, 255, 255, 255);
                            }
                        }
                    }
                }
            }
        }
    }
}

void DSTriangleBatcher::renderTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color &color)
{
    TRIANGLE t = {x1, y1, x2, y2, x3, y3};
    m_triangles.push_back(t);

    m_iNumTriangles++;
}

void DSTriangleBatcher::setPixel(uint8_t *framebuffer, int x, int y, int red, int green, int blue)
{
    framebuffer[3 * (y + x * 240)] = blue;
    framebuffer[3 * (y + x * 240) + 1] = green;
    framebuffer[3 * (y + x * 240) + 2] = red;
}