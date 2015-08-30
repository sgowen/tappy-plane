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
#include "GameConstants.h"
#include "GpuProgramWrapper.h"

#include <sstream>

#include <3ds.h>

#include <sf2d.h>

#include <stdio.h>

#include <string.h>

extern "C"
{
    extern const struct
    {
        unsigned int width;
        unsigned int height;
        unsigned int bytes_per_pixel;
        unsigned char pixel_data[];
    } game;

    extern const struct
    {
        unsigned int width;
        unsigned int height;
        unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
        unsigned char pixel_data[];
    } background;
}

sf2d_texture *backgroundTex;
sf2d_texture *gameTex;

DSRenderer::DSRenderer(gfxScreen_t screen, int screenWidth, int screenHeight) : Renderer(), m_screen(screen)
{
    m_spriteBatcher = std::unique_ptr<DSSpriteBatcher>(new DSSpriteBatcher(screen, screenWidth, screenHeight));

    backgroundTex = sf2d_create_texture_mem_RGBA8(background.pixel_data, background.width, background.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    gameTex = sf2d_create_texture_mem_RGBA8(game.pixel_data, game.width, game.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);

    m_backgroundTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(backgroundTex));
    m_gameTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(gameTex));
}

DSRenderer::~DSRenderer()
{
    cleanUp();
}

void DSRenderer::clearScreenWithColor(float r, float g, float b, float a)
{
    sf2d_set_clear_color(RGBA8((int) (r * 255), (int) (g * 255), (int) (b * 255), (int) (a * 255)));
}

void DSRenderer::beginFrame()
{
    sf2d_start_frame(m_screen, GFX_LEFT);
}

void DSRenderer::endFrame()
{
    sf2d_end_frame();
}

void DSRenderer::cleanUp()
{
    sf2d_free_texture(backgroundTex);
    sf2d_free_texture(gameTex);
}

void DSRenderer::renderWorldBackground(World &world)
{
    m_spriteBatcher->beginBatch();
    m_spriteBatcher->drawSprite(WORLD_BACKGROUND_X * 2, WORLD_BACKGROUND_Y, WORLD_BACKGROUND_WIDTH * 2, WORLD_BACKGROUND_HEIGHT, 0, Assets::getWorldBackgroundTextureRegion());
    m_spriteBatcher->endBatch(*m_backgroundTexture);
}

void DSRenderer::renderWorldForeground(World &world, Glove &glove, float titleAlpha)
{
    m_spriteBatcher->beginBatch();
    for (std::vector<std::unique_ptr<Obstacle>>::iterator itr = world.getObstacles().begin(); itr != world.getObstacles().end(); ++itr)
    {
        renderObstacle((**itr));
    }
    m_spriteBatcher->endBatch(*m_gameTexture);
    
    m_spriteBatcher->beginBatch();
    renderPhysicalEntity(world.getPlane(), Assets::getPlaneTextureRegion(world.getPlane()));
    m_spriteBatcher->endBatch(*m_gameTexture);
    
    if(world.getPlane().getPuffClouds().size() > 0)
    {
        m_spriteBatcher->beginBatch();
        
        for (std::vector<std::unique_ptr<PuffCloud>>::iterator itr = world.getPlane().getPuffClouds().begin(); itr != world.getPlane().getPuffClouds().end(); itr++)
        {
			Color puffCloudColor = Color(1, 1, 1, (*itr)->getAlpha());
            m_spriteBatcher->drawSprite((*itr)->getPosition().getX(), (*itr)->getPosition().getY(), (*itr)->getWidth(), (*itr)->getHeight(), (*itr)->getAngle(), puffCloudColor, Assets::getPuffLargeTextureRegion());
        }
        
        m_spriteBatcher->endBatch(*m_gameTexture);
    }
    
    // Bottom Bar (foreground)
    m_spriteBatcher->beginBatch();
    m_spriteBatcher->drawSprite(world.getForegroundLeft().getPosition().getX() * 2, world.getForegroundLeft().getPosition().getY(), world.getForegroundLeft().getWidth() * 2, world.getForegroundLeft().getHeight(), 0, Assets::getWorldForegroundLeftTextureRegion(world.getEnvironmentType()));
    m_spriteBatcher->drawSprite(world.getForegroundRight().getPosition().getX() * 2, world.getForegroundRight().getPosition().getY(), world.getForegroundRight().getWidth() * 2, world.getForegroundRight().getHeight(), 0, Assets::getWorldForegroundRightTextureRegion(world.getEnvironmentType()));
    m_spriteBatcher->endBatch(*m_gameTexture);
    
    if(titleAlpha > 0)
    {
        Color titleColor = Color(1, 1, 1, titleAlpha);
        
        m_spriteBatcher->beginBatch();
        m_spriteBatcher->drawSprite(TITLE_X, TITLE_Y, TITLE_WIDTH, TITLE_HEIGHT, 0, titleColor, Assets::getTitleTextureRegion());
        m_spriteBatcher->drawSprite(glove.getPosition().getX(), glove.getPosition().getY(), glove.getWidth(), glove.getHeight(), glove.getAngle(), titleColor, Assets::getGloveTextureRegion(glove));
        m_spriteBatcher->drawSprite(glove.getPosition().getX() - 3.5f, glove.getPosition().getY(), 4, 2, 0, titleColor, Assets::getTapLeftTextureRegion());
        m_spriteBatcher->drawSprite(glove.getPosition().getX() + 3.5f, glove.getPosition().getY(), 4, 2, 0, titleColor, Assets::getTapRightTextureRegion());
        m_spriteBatcher->endBatch(*m_backgroundTexture);
    }
    
    if(!world.isGameOver() && world.getScore() > 0 && titleAlpha < 0)
    {
        std::stringstream ss;
        ss << world.getScore();
        std::string score = ss.str();
		static Color scoreColor = Color(1, 1, 1, 1);
        
        m_spriteBatcher->beginBatch();
        m_font->renderText(*m_spriteBatcher, score, SCORE_FONT_X, SCORE_FONT_Y, SCORE_FONT_WIDTH, SCORE_FONT_HEIGHT, scoreColor, true, false, 16);
        m_spriteBatcher->endBatch(*m_gameTexture);
    }
}