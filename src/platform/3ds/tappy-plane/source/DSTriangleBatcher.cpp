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

DSTriangleBatcher::DSTriangleBatcher(gfxScreen_t screen, int screenWidth, int screenHeight, bool isFill) : TriangleBatcher(isFill), m_screen(screen), m_iScreenWidth(screenWidth), m_iScreenHeight(screenHeight)
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
        u8* fb = gfxGetFramebuffer(m_screen, GFX_LEFT, NULL, NULL);

        int left, top, right, bottom, x1, y1, x2, y2, x3, y3;

        for (std::vector<TRIANGLE>::iterator itr = m_triangles.begin(); itr != m_triangles.end(); ++itr)
        {
            TRIANGLE tri = *itr;

            x1 = (int) (tri.x1 / GAME_WIDTH * (m_iScreenWidth - 1));
            y1 = (int) (tri.y1 / GAME_HEIGHT * (m_iScreenHeight - 1));

            x2 = (int) (tri.x2 / GAME_WIDTH * (m_iScreenWidth - 1));
            y2 = (int) (tri.y2 / GAME_HEIGHT * (m_iScreenHeight - 1));

            x3 = (int) (tri.x3 / GAME_WIDTH * (m_iScreenWidth - 1));
            y3 = (int) (tri.y3 / GAME_HEIGHT * (m_iScreenHeight - 1));

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
                if (x >= 0 && x < m_iScreenWidth)
                {
                    for (int y = bottom; y < top; y++)
                    {
                        if (y >= 0 && y < m_iScreenHeight)
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