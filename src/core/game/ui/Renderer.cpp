//
//  Renderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/13/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "Renderer.h"
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

#include <sstream>

Renderer::Renderer()
{
    m_font = std::unique_ptr<Font>(new Font(FONT_TEXTURE_REGION_X, FONT_TEXTURE_REGION_Y, FONT_GLYPHS_PER_ROW, FONT_GLYPH_WIDTH, FONT_GLYPH_HEIGHT, TEXTURE_SIZE_1024x1024, TEXTURE_SIZE_1024x1024));
}

void Renderer::renderWorldBackground(World &world)
{
    m_spriteBatcher->beginBatch();
    m_spriteBatcher->drawSprite(WORLD_BACKGROUND_X, WORLD_BACKGROUND_Y, WORLD_BACKGROUND_WIDTH, WORLD_BACKGROUND_HEIGHT, 0, Assets::getWorldBackgroundTextureRegion());
    m_spriteBatcher->endBatchWithTexture(*m_backgroundTexture);
}

void Renderer::renderWorldForeground(World &world, Glove &glove, float titleAlpha)
{
    m_spriteBatcher->beginBatch();
    for (std::vector<std::unique_ptr<Obstacle>>::iterator itr = world.getObstacles().begin(); itr != world.getObstacles().end(); ++itr)
    {
        renderObstacle((**itr));
    }
    m_spriteBatcher->endBatchWithTexture(*m_gameTexture);
    
    m_spriteBatcher->beginBatch();
    renderPhysicalEntity(world.getPlane(), Assets::getPlaneTextureRegion(world.getPlane()));
    m_spriteBatcher->endBatchWithTexture(*m_gameTexture);
    
    if(world.getPlane().getPuffClouds().size() > 0)
    {
        m_spriteBatcher->beginBatch();
        
        for (std::vector<std::unique_ptr<PuffCloud>>::iterator itr = world.getPlane().getPuffClouds().begin(); itr != world.getPlane().getPuffClouds().end(); itr++)
        {
			Color puffCloudColor = Color(1, 1, 1, (*itr)->getAlpha());
            m_spriteBatcher->drawSprite((*itr)->getPosition().getX(), (*itr)->getPosition().getY(), (*itr)->getWidth(), (*itr)->getHeight(), (*itr)->getAngle(), puffCloudColor, Assets::getPuffLargeTextureRegion());
        }
        
        m_spriteBatcher->endBatchWithTexture(*m_gameTexture);
    }
    
    // Bottom Bar (foreground)
    m_spriteBatcher->beginBatch();
    renderPhysicalEntity(world.getForegroundLeft(), Assets::getWorldForegroundLeftTextureRegion(world.getEnvironmentType()));
    renderPhysicalEntity(world.getForegroundRight(), Assets::getWorldForegroundRightTextureRegion(world.getEnvironmentType()));
    m_spriteBatcher->endBatchWithTexture(*m_gameTexture);
    
    if(titleAlpha > 0)
    {
        Color titleColor = Color(1, 1, 1, titleAlpha);
        
        m_spriteBatcher->beginBatch();
        m_spriteBatcher->drawSprite(TITLE_X, TITLE_Y, TITLE_WIDTH, TITLE_HEIGHT, 0, titleColor, Assets::getTitleTextureRegion());
        m_spriteBatcher->drawSprite(glove.getPosition().getX(), glove.getPosition().getY(), glove.getWidth(), glove.getHeight(), glove.getAngle(), titleColor, Assets::getGloveTextureRegion(glove));
        m_spriteBatcher->drawSprite(glove.getPosition().getX() - 3.5f, glove.getPosition().getY(), 4, 2, 0, titleColor, Assets::getTapLeftTextureRegion());
        m_spriteBatcher->drawSprite(glove.getPosition().getX() + 3.5f, glove.getPosition().getY(), 4, 2, 0, titleColor, Assets::getTapRightTextureRegion());
        m_spriteBatcher->endBatchWithTexture(*m_backgroundTexture);
    }
    
    if(!world.isGameOver() && world.getScore() > 0 && titleAlpha < 0)
    {
        std::stringstream ss;
        ss << world.getScore();
        std::string score = ss.str();
		static Color scoreColor = Color(1, 1, 1, 1);
        
        m_spriteBatcher->beginBatch();
        m_font->renderText(*m_spriteBatcher, score, SCORE_FONT_X, SCORE_FONT_Y, SCORE_FONT_WIDTH, SCORE_FONT_HEIGHT, scoreColor, true, false, 16);
        m_spriteBatcher->endBatchWithTexture(*m_gameTexture);
    }
}

void Renderer::renderWorldGameOver(World &world, GameButton &okButton, GameButton &leaderboardsButton, int bestScore)
{
    m_spriteBatcher->beginBatch();
    m_spriteBatcher->drawSprite(GAME_OVER_X, GAME_OVER_Y, GAME_OVER_WIDTH, GAME_OVER_HEIGHT, 0, Assets::getGameOverTextureRegion());
    m_spriteBatcher->drawSprite(DIALOG_GAME_OVER_X, DIALOG_GAME_OVER_Y, DIALOG_GAME_OVER_WIDTH, DIALOG_GAME_OVER_HEIGHT, 0, Assets::getDialogTextureRegion());
    renderPhysicalEntity(okButton, Assets::getOkButtonTextureRegion());
    renderPhysicalEntity(leaderboardsButton, Assets::getLeaderboardsButtonTextureRegion());
    
    if(world.getScore() >= 50)
    {
        m_spriteBatcher->drawSprite(MEDAL_X, MEDAL_Y, MEDAL_WIDTH, MEDAL_HEIGHT, 0, Assets::getGoldMedalTextureRegion());
    }
    else if(world.getScore() >= 25)
    {
        m_spriteBatcher->drawSprite(MEDAL_X, MEDAL_Y, MEDAL_WIDTH, MEDAL_HEIGHT, 0, Assets::getSilverMedalTextureRegion());
    }
    else if(world.getScore() >= 10)
    {
        m_spriteBatcher->drawSprite(MEDAL_X, MEDAL_Y, MEDAL_WIDTH, MEDAL_HEIGHT, 0, Assets::getBronzeMedalTextureRegion());
    }
    
    m_spriteBatcher->endBatchWithTexture(*m_gameTexture);
    
    std::stringstream ss;
    ss << world.getScore();
    std::string scoreString = ss.str();
    
    std::stringstream ss2;
    ss2 << bestScore;
    std::string bestScoreString = ss2.str();
    
	static Color scoreColor = Color(1, 1, 1, 1);
    
    m_spriteBatcher->beginBatch();
    m_font->renderText(*m_spriteBatcher, scoreString, SCORE_FONT_IN_WINDOW_X, SCORE_FONT_IN_WINDOW_Y, FONT_IN_WINDOW_WIDTH, FONT_IN_WINDOW_HEIGHT, scoreColor, false, true, 16);
    m_font->renderText(*m_spriteBatcher, bestScoreString, BEST_FONT_IN_WINDOW_X, BEST_FONT_IN_WINDOW_Y, FONT_IN_WINDOW_WIDTH, FONT_IN_WINDOW_HEIGHT, scoreColor, false, true, 16);
    m_spriteBatcher->endBatchWithTexture(*m_gameTexture);
}

void Renderer::renderObstacle(Obstacle &obstacle)
{
    for (std::vector<std::unique_ptr<SpikePhysicalEntity>>::iterator itr = obstacle.getSpikes().begin(); itr != obstacle.getSpikes().end(); ++itr)
    {
        renderPhysicalEntity((**itr), Assets::getWorldSpikeTextureRegion((**itr).getType()));
    }
}

void Renderer::renderPhysicalEntity(PhysicalEntity &go, TextureRegion tr)
{
    m_spriteBatcher->drawSprite(go.getPosition().getX(), go.getPosition().getY(), go.getWidth(), go.getHeight(), go.getAngle(), tr);
}