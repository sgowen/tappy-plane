//
//  DSGameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "DSGameScreen.h"
#include "TouchEvent.h"
#include "Vector2D.h"
#include "DSRenderer.h"
#include "GameConstants.h"
#include "SpriteBatcher.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Font.h"
#include "GameButton.h"
#include "TopScreenRenderer.h"

#include <3ds.h>

#include <sf2d.h>

#include <string.h>

DSGameScreen::DSGameScreen(int topScreenWidth, int topScreenHeight, int bottomScreenWidth, int bottomScreenHeight) : GameScreen()
{
    sf2d_init(GAME_WIDTH, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT);

    m_renderer = std::unique_ptr<DSRenderer>(new DSRenderer(GFX_BOTTOM, bottomScreenWidth, bottomScreenHeight));
    topScreenRenderer = new TopScreenRenderer(GFX_TOP, 400, 240);

    m_iTopScreenWidth = topScreenWidth;
    m_iTopScreenHeight = topScreenHeight;
    m_iBottomScreenWidth = bottomScreenWidth;
    m_iBottomScreenHeight = bottomScreenHeight;
}

void DSGameScreen::touchToWorld(TouchEvent &touchEvent)
{
    float x = (touchEvent.getX() / (float) m_iBottomScreenWidth) * GAME_WIDTH;
    float y = (((float) m_iBottomScreenHeight) - touchEvent.getY()) / ((float) m_iBottomScreenHeight) * GAME_HEIGHT;

    m_touchPoint->set(x, y);
}

void DSGameScreen::platformResume()
{
    // Empty
}

void DSGameScreen::platformPause()
{
    // Empty
}

void DSGameScreen::render()
{
    GameScreen::render();

    topScreenRenderer->beginFrame();
    topScreenRenderer->render();
    topScreenRenderer->endFrame();

    sf2d_swapbuffers();
}

void DSGameScreen::exit()
{
    m_renderer->cleanUp();
    topScreenRenderer->cleanUp();

    sf2d_fini();
}