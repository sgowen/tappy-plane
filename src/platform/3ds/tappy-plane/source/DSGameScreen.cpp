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

#include <3ds.h>

#include <string.h>

DSGameScreen::DSGameScreen(int topScreenWidth, int topScreenHeight, int bottomScreenWidth, int bottomScreenHeight) : GameScreen()
{
    m_renderer = std::unique_ptr<DSRenderer>(new DSRenderer(GFX_BOTTOM, bottomScreenWidth, bottomScreenHeight));

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