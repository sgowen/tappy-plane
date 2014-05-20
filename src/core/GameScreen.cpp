//
//  GameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "GameScreen.h"
#include "Vector2D.h"
#include "TouchEvent.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include "Assets.h"
#include "OverlapTester.h"
#include "GameButton.h"
#include "Glove.h"

GameScreen::GameScreen()
{
    init();
}

void GameScreen::init()
{
    m_touchPoint = std::unique_ptr<Vector2D>(new Vector2D());
    m_glove = std::unique_ptr<Glove>(new Glove(SCREEN_WIDTH_1_2, SCREEN_HEIGHT_1_2 - 4, 2, 2));
    m_world = std::unique_ptr<World>(new World());
    m_okButton = std::unique_ptr<GameButton>(new GameButton(5.4f, 8.6f, 3.6f, 2.11764706f));
    m_leaderboardsButton = std::unique_ptr<GameButton>(new GameButton(11.6f, 8.6f, 6.0f, 2.20408163f));
    m_gameState = WAITING;
    m_iScreenState = 0;
    m_fColor = 0;
    m_fTitleAlpha = 1;
	m_iBestScore = 0;
}

void GameScreen::onResume()
{
	if(m_gameState == RUNNING)
	{
        m_world->startGame();
        platformResume();
	}
}

void GameScreen::onPause()
{
    platformPause();
}

void GameScreen::update(float deltaTime, std::vector<TouchEvent> &touchEvents)
{
    m_world->update(deltaTime);
    
    switch (m_gameState)
    {
        case WAITING:
            updateWaiting(deltaTime);
            updateInputWaiting(touchEvents);
            break;
        case GAME_OVER:
            updateGameOver(deltaTime);
            updateInputGameOver(touchEvents);
            break;
        case RUNNING:
        default:
            m_fTitleAlpha -= deltaTime * 2;
            updateRunning(deltaTime);
            updateInputRunning(touchEvents);
            break;
    }
}

int GameScreen::getState()
{
	return m_iScreenState;
}

void GameScreen::clearState()
{
    m_iScreenState = 0;
}

int GameScreen::getScore()
{
    return m_world->getScore();
}

void GameScreen::setBestScore(int bestScore)
{
    m_iBestScore = bestScore;
}

void GameScreen::updateWaiting(float deltaTime)
{
    m_glove->update(deltaTime);
}

void GameScreen::updateRunning(float deltaTime)
{
    if(m_world->isGameOver())
    {
        m_gameState = GAME_OVER;
        m_iScreenState = 3;
    }
}

void GameScreen::updateGameOver(float deltaTime)
{
    
}

void GameScreen::updateInputWaiting(std::vector<TouchEvent> &touchEvents)
{
    for (std::vector<TouchEvent>::iterator itr = touchEvents.begin(); itr != touchEvents.end(); itr++)
	{
		touchToWorld((*itr));
		
		switch (itr->getTouchType())
		{
            case DOWN:
				m_gameState = Game_State::RUNNING;
				onResume();
				m_world->handleTouchUp(*itr);
				continue;
            case DRAGGED:
                continue;
            case UP:
                // Nothing
                return;
		}
	}
}

void GameScreen::updateInputRunning(std::vector<TouchEvent> &touchEvents)
{
    for (std::vector<TouchEvent>::iterator itr = touchEvents.begin(); itr != touchEvents.end(); itr++)
	{
		touchToWorld((*itr));
		
		switch (itr->getTouchType())
		{
            case DOWN:
                m_world->handleTouchUp(*itr);
                continue;
            case DRAGGED:
                continue;
            case UP:
                // Nothing
                return;
		}
	}
}

void GameScreen::updateInputGameOver(std::vector<TouchEvent> &touchEvents)
{
    for (std::vector<TouchEvent>::iterator itr = touchEvents.begin(); itr != touchEvents.end(); itr++)
	{
		touchToWorld((*itr));
		
		switch (itr->getTouchType())
		{
            case DOWN:
                continue;
            case DRAGGED:
                continue;
            case UP:
                if(OverlapTester::isPointInRectangle(*m_touchPoint, m_okButton->getBounds()))
                {
                    init();
                }
                else if(OverlapTester::isPointInRectangle(*m_touchPoint, m_leaderboardsButton->getBounds()))
                {
                    // Show leaderboards
                    m_iScreenState = 4;
                }
                return;
		}
	}
}