//
//  OpenGLESRenderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "OpenGLESRenderer.h"
#include "SpriteBatcher.h"
#include "PlaneDynamicGameObject.h"
#include "TextureRegion.h"
#include "Vector2D.h"
#include "Assets.h"
#include "World.h"
#include "Obstacle.h"
#include "Font.h"
#include "GameButton.h"
#include "Glove.h"
#include "PuffCloud.h"
#include <sstream>

extern "C"
{
#include "asset_utils.h"
}

OpenGLESRenderer::OpenGLESRenderer() : Renderer()
{
    m_spriteBatcher = std::unique_ptr<SpriteBatcher>(new SpriteBatcher(1000, false));
    m_spriteBatcherWithColor = std::unique_ptr<SpriteBatcher>(new SpriteBatcher(1000, true));
    
    m_gameTexture = load_png_asset_into_texture("game.png");
    m_backgroundTexture = load_png_asset_into_texture("background.png");
}

void OpenGLESRenderer::renderWorldBackground(World &world)
{
    m_spriteBatcher->beginBatch();
    m_spriteBatcher->drawSprite(WORLD_BACKGROUND_X, WORLD_BACKGROUND_Y, WORLD_BACKGROUND_WIDTH, WORLD_BACKGROUND_HEIGHT, 0, Assets::getWorldBackgroundTextureRegion());
    m_spriteBatcher->endBatchWithTexture(m_backgroundTexture);
}

void OpenGLESRenderer::renderWorldForeground(World &world, Glove &glove, float titleAlpha)
{
    m_spriteBatcher->beginBatch();
    for (std::vector<std::unique_ptr<Obstacle>>::iterator itr = world.getObstacles().begin(); itr != world.getObstacles().end(); ++itr)
	{
        renderObstacle((**itr));
	}
    m_spriteBatcher->endBatchWithTexture(m_gameTexture);
    
    m_spriteBatcher->beginBatch();
    renderGameObject(world.getPlane(), Assets::getPlaneTextureRegion(world.getPlane()));
    m_spriteBatcher->endBatchWithTexture(m_gameTexture);
    
    if(world.getPlane().getPuffClouds().size() > 0)
    {
        m_spriteBatcherWithColor->beginBatch();
        
        for (std::vector<std::unique_ptr<PuffCloud>>::iterator itr = world.getPlane().getPuffClouds().begin(); itr != world.getPlane().getPuffClouds().end(); itr++)
        {
            Color puffCloudColor = { 1, 1, 1, (*itr)->getAlpha() };
            m_spriteBatcherWithColor->drawSprite((*itr)->getPosition().getX(), (*itr)->getPosition().getY(), (*itr)->getWidth(), (*itr)->getHeight(), (*itr)->getAngle(), puffCloudColor, Assets::getPuffLargeTextureRegion());
        }
        
        m_spriteBatcherWithColor->endBatchWithTexture(m_gameTexture);
    }
    
    // Bottom Bar (foreground)
    m_spriteBatcher->beginBatch();
    renderGameObject(world.getForegroundLeft(), Assets::getWorldForegroundLeftTextureRegion(world.getEnvironmentType()));
    renderGameObject(world.getForegroundRight(), Assets::getWorldForegroundRightTextureRegion(world.getEnvironmentType()));
    m_spriteBatcher->endBatchWithTexture(m_gameTexture);
    
    if(titleAlpha > 0)
    {
        Color titleColor = { 1, 1, 1, titleAlpha };
        
        m_spriteBatcherWithColor->beginBatch();
        m_spriteBatcherWithColor->drawSprite(TITLE_X, TITLE_Y, TITLE_WIDTH, TITLE_HEIGHT, 0, titleColor, Assets::getTitleTextureRegion());
        m_spriteBatcherWithColor->drawSprite(glove.getPosition().getX(), glove.getPosition().getY(), glove.getWidth(), glove.getHeight(), glove.getAngle(), titleColor, Assets::getGloveTextureRegion(glove));
        m_spriteBatcherWithColor->drawSprite(glove.getPosition().getX() - 3.5f, glove.getPosition().getY(), 4, 2, 0, titleColor, Assets::getTapLeftTextureRegion());
        m_spriteBatcherWithColor->drawSprite(glove.getPosition().getX() + 3.5f, glove.getPosition().getY(), 4, 2, 0, titleColor, Assets::getTapRightTextureRegion());
        m_spriteBatcherWithColor->endBatchWithTexture(m_backgroundTexture);
    }
    
    if(!world.isGameOver() && world.getScore() > 0 && titleAlpha < 0)
    {
        std::stringstream ss;
        ss << world.getScore();
        std::string score = ss.str();
        static Color scoreColor = { 1, 1, 1, 1 };
        
        m_spriteBatcherWithColor->beginBatch();
        m_font->renderText(*m_spriteBatcherWithColor, score, SCORE_FONT_X, SCORE_FONT_Y, SCORE_FONT_WIDTH, SCORE_FONT_HEIGHT, scoreColor, true);
        m_spriteBatcherWithColor->endBatchWithTexture(m_gameTexture);
    }
}

void OpenGLESRenderer::renderWorldGameOver(World &world, GameButton &okButton, GameButton &leaderboardsButton, int bestScore)
{
    m_spriteBatcher->beginBatch();
    m_spriteBatcher->drawSprite(GAME_OVER_X, GAME_OVER_Y, GAME_OVER_WIDTH, GAME_OVER_HEIGHT, 0, Assets::getGameOverTextureRegion());
    m_spriteBatcher->drawSprite(DIALOG_GAME_OVER_X, DIALOG_GAME_OVER_Y, DIALOG_GAME_OVER_WIDTH, DIALOG_GAME_OVER_HEIGHT, 0, Assets::getDialogTextureRegion());
    renderGameObject(okButton, Assets::getOkButtonTextureRegion());
    renderGameObject(leaderboardsButton, Assets::getLeaderboardsButtonTextureRegion());
    
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
    
    m_spriteBatcher->endBatchWithTexture(m_gameTexture);
    
    std::stringstream ss;
    ss << world.getScore();
    std::string scoreString = ss.str();
    
    std::stringstream ss2;
    ss2 << bestScore;
    std::string bestScoreString = ss2.str();
    
    static Color scoreColor = { 1, 1, 1, 1 };
    
    m_spriteBatcherWithColor->beginBatch();
    m_font->renderText(*m_spriteBatcherWithColor, scoreString, SCORE_FONT_IN_WINDOW_X, SCORE_FONT_IN_WINDOW_Y, FONT_IN_WINDOW_WIDTH, FONT_IN_WINDOW_HEIGHT, scoreColor, false, true);
    m_font->renderText(*m_spriteBatcherWithColor, bestScoreString, BEST_FONT_IN_WINDOW_X, BEST_FONT_IN_WINDOW_Y, FONT_IN_WINDOW_WIDTH, FONT_IN_WINDOW_HEIGHT, scoreColor, false, true);
    m_spriteBatcherWithColor->endBatchWithTexture(m_gameTexture);
}

void OpenGLESRenderer::renderObstacle(Obstacle &obstacle)
{
    for (std::vector<std::unique_ptr<SpikeGameObject>>::iterator itr = obstacle.getSpikes().begin(); itr != obstacle.getSpikes().end(); ++itr)
    {
        renderGameObject((**itr), Assets::getWorldSpikeTextureRegion((**itr).getType()));
    }
}

void OpenGLESRenderer::renderGameObject(GameObject &go, TextureRegion tr)
{
    m_spriteBatcher->drawSprite(go.getPosition().getX(), go.getPosition().getY(), go.getWidth(), go.getHeight(), go.getAngle(), tr);
}