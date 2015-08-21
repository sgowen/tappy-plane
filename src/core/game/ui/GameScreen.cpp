//
//  GameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "GameScreen.h"
#include "Vector2D.h"
#include "TouchEvent.h"
#include "Vector2D.h"
#include "Rectangle.h"
#include "Assets.h"
#include "OverlapTester.h"
#include "GameButton.h"
#include "Glove.h"
#include "Renderer.h"
#include "GameConstants.h"
#include "World.h"
#include "TextureWrapper.h"
#include "SpriteBatcher.h"
#include "Font.h"

GameScreen::GameScreen()
{
    init();
}

void GameScreen::init()
{
    m_touchPoint = std::unique_ptr<Vector2D>(new Vector2D());

    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));
    m_touchEventsPool.push_back(TouchEvent(0, 0, Touch_Type::DOWN));

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
    if (m_gameState == RUNNING)
    {
        m_world->startGame();
        platformResume();
    }
}

void GameScreen::onPause()
{
    platformPause();
}

void GameScreen::update(float deltaTime)
{
    for (std::vector<TouchEvent>::iterator itr = m_touchEvents.begin(); itr != m_touchEvents.end(); itr++)
    {
        if (m_touchEventsPool.size() < 50)
        {
            m_touchEventsPool.push_back(*itr);
        }
    }

    m_touchEvents.clear();
    m_touchEvents.swap(m_touchEventsBuffer);
    m_touchEventsBuffer.clear();

    m_world->update(deltaTime);

    switch (m_gameState)
    {
    case WAITING:
        updateWaiting(deltaTime);
        updateInputWaiting(m_touchEvents);
        break;
    case GAME_OVER:
        updateGameOver(deltaTime);
        updateInputGameOver(m_touchEvents);
        break;
    case RUNNING:
    default:
        m_fTitleAlpha -= deltaTime * 2;
        updateRunning(deltaTime);
        updateInputRunning(m_touchEvents);
        break;
    }
}

void GameScreen::present()
{
    m_renderer->clearScreenWithColor(m_fColor, m_fColor, m_fColor, 1);

    m_renderer->beginFrame();

    m_renderer->renderWorldBackground(*m_world);

    m_renderer->renderWorldForeground(*m_world, *m_glove, m_fTitleAlpha);

    if (m_gameState == GAME_OVER)
    {
        m_renderer->renderWorldGameOver(*m_world, *m_okButton, *m_leaderboardsButton, m_iBestScore);
    }

    m_renderer->endFrame();
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

short GameScreen::getCurrentSoundId()
{
    short playThisSound = Assets::getInstance()->getFirstSoundId();
    Assets::getInstance()->eraseFirstSoundId();
    return playThisSound;
}

void GameScreen::onTouch(Touch_Type type, float raw_touch_x, float raw_touch_y)
{
    if (type == Touch_Type::DRAGGED && m_touchEventsBuffer.size() > 3)
    {
        return;
    }

    addTouchEventForType(type, raw_touch_x, raw_touch_y);
}

#pragma mark private

TouchEvent GameScreen::newTouchEvent()
{
    if (m_touchEventsPool.size() == 0)
    {
        return TouchEvent(0, 0, Touch_Type::DOWN);
    }
    else
    {
        TouchEvent touchEvent = m_touchEventsPool.back();
        m_touchEventsPool.pop_back();
        return touchEvent;
    }
}

void GameScreen::addTouchEventForType(Touch_Type touchType, float x, float y)
{
    TouchEvent touchEvent = newTouchEvent();
    touchEvent.setTouchType(touchType);
    touchEvent.setX(x);
    touchEvent.setY(y);

    m_touchEventsBuffer.push_back(touchEvent);
}

void GameScreen::updateWaiting(float deltaTime)
{
    m_glove->update(deltaTime);
}

void GameScreen::updateRunning(float deltaTime)
{
    if (m_world->isGameOver())
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
            if (OverlapTester::isPointInRectangle(*m_touchPoint, m_okButton->getBounds()))
            {
                init();
            }
            else if (OverlapTester::isPointInRectangle(*m_touchPoint, m_leaderboardsButton->getBounds()))
            {
                // Show leaderboards
                m_iScreenState = 4;
            }
            return;
        }
    }
}