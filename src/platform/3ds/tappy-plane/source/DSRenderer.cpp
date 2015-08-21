//
//  DSRenderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "DSRenderer.h"
#include "DSSpriteBatcher.h"
#include "RectangleBatcher.h"
#include "LineBatcher.h"
#include "CircleBatcher.h"
#include "Font.h"
#include "TextureWrapper.h"
#include "GameConstants.h"
#include "ResourceConstants.h"
#include "SpriteBatcher.h"
#include "Circle.h"
#include "Color.h"
#include "TextureRegion.h"
#include "Assets.h"
#include "Vector2D.h"
#include "Font.h"
#include "TextureWrapper.h"
#include "Rectangle.h"
#include "PhysicalEntity.h"
#include "World.h"
#include "GameConstants.h"
#include "PuffCloud.h"
#include "PlanePhysicalEntity.h"
#include "Glove.h"
#include "GameButton.h"
#include "DSTriangleBatcher.h"

#include <sstream>

#include <3ds.h>

#include <stdio.h>

#include <string.h>

DSRenderer::DSRenderer() : Renderer()
{
    m_spriteBatcher = std::unique_ptr<DSSpriteBatcher>(new DSSpriteBatcher());

    m_backgroundTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper());
    m_gameTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper());

    m_triangleBatcher = std::unique_ptr<DSTriangleBatcher>(new DSTriangleBatcher(true));

    //Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    consoleInit(GFX_BOTTOM, NULL);
}

void DSRenderer::clearScreenWithColor(float r, float g, float b, float a)
{
    // Please note that the 3DS screens are sideways (thus 240x400 and 240x320)
    u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    memset(fb, 0, 240 * 400 * 3);
}

void DSRenderer::beginFrame()
{
    // TODO
}

void DSRenderer::endFrame()
{
    // TODO
}

void DSRenderer::cleanUp()
{
    // TODO
}

void DSRenderer::renderWorldBackground(World &world)
{
    static Color bgColor = Color(0.2, 0.2, 0.2, 0.2);

    m_spriteBatcher->beginBatch();
    m_spriteBatcher->drawSprite(WORLD_BACKGROUND_X, WORLD_BACKGROUND_Y, WORLD_BACKGROUND_WIDTH, WORLD_BACKGROUND_HEIGHT, 0, bgColor, Assets::getWorldBackgroundTextureRegion());
    m_spriteBatcher->endBatchWithTexture(*m_backgroundTexture);
}

void DSRenderer::renderWorldForeground(World &world, Glove &glove, float titleAlpha)
{
    m_triangleBatcher->beginBatch();
    for (std::vector < std::unique_ptr < Obstacle >> ::iterator itr = world.getObstacles().begin(); itr != world.getObstacles().end(); ++itr)
    {
        static Color whiteColor = Color(1, 1, 1, 1);
        m_triangleBatcher->renderTriangle((**itr).getTopBounds(), whiteColor);
        m_triangleBatcher->renderTriangle((**itr).getBottomBounds(), whiteColor);
    }
    m_triangleBatcher->endBatch();

    m_spriteBatcher->beginBatch();
    float width = world.getPlane().getBounds().getWidth();
    float height = world.getPlane().getBounds().getHeight();
    float planeX = world.getPlane().getBounds().getLowerLeft().getX() + width / 2;
    float planeY = world.getPlane().getBounds().getLowerLeft().getY() + height / 2;
    m_spriteBatcher->drawSprite(planeX, planeY, width, height, 0, Assets::getPlaneTextureRegion(world.getPlane()));
    m_spriteBatcher->endBatchWithTexture(*m_gameTexture);

    // Bottom Bar (foreground)
    m_spriteBatcher->beginBatch();
    renderPhysicalEntity(world.getForegroundLeft(), Assets::getWorldForegroundLeftTextureRegion(world.getEnvironmentType()));
    renderPhysicalEntity(world.getForegroundRight(), Assets::getWorldForegroundRightTextureRegion(world.getEnvironmentType()));
    m_spriteBatcher->endBatchWithTexture(*m_gameTexture);

    if (titleAlpha > 0)
    {
        printf("\x1b[15;12HTap A to start");
    }
    else
    {
        printf("\x1b[15;12H              ");
    }

    if (!world.isGameOver() && world.getScore() > 0 && titleAlpha < 0)
    {
        std::stringstream ss;
        ss << world.getScore();
        std::string score = ss.str();

        //Move the cursor to row 15 and column 19 and then prints "Hello World!"
        //To move the cursor you have to print "\x1b[r;cH", where r and c are respectively
        //the row and column where you want your cursor to move
        //The top screen has 30 rows and 50 columns
        //The bottom screen has 30 rows and 40 columns
        printf("\x1b[5;19H%s", score.c_str());
    }
}

void DSRenderer::renderWorldGameOver(World &world, GameButton &okButton, GameButton &leaderboardsButton, int bestScore)
{
    printf("\x1b[15;15HGame Over!");
    printf("\x1b[17;12HTap A to restart");
}