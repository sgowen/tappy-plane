//
//  AndroidOpenGLESGameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 7/22/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "AndroidOpenGLESGameScreen.h"
#include "TouchEvent.h"
#include "Vector2D.h"
#include "OpenGLESRenderer.h"
#include "OpenGLESManager.h"
#include "GameConstants.h"
#include "SpriteBatcher.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Font.h"
#include "GameButton.h"

AndroidOpenGLESGameScreen::AndroidOpenGLESGameScreen() : OpenGLESGameScreen()
{
    // Empty
}

void AndroidOpenGLESGameScreen::onSurfaceCreated(int screenWidth, int screenHeight)
{
    onSurfaceChanged(screenWidth, screenHeight);
}

void AndroidOpenGLESGameScreen::onSurfaceChanged(int screenWidth, int screenHeight)
{
    m_iScreenWidth = screenWidth;
    m_iScreenHeight = screenHeight;

    initGraphics(screenWidth, screenHeight);
}

void AndroidOpenGLESGameScreen::touchToWorld(TouchEvent &touchEvent)
{
    m_touchPoint->set((touchEvent.getX() / (float) m_iScreenWidth) * GAME_WIDTH, (1 - touchEvent.getY() / (float) m_iScreenHeight) * GAME_HEIGHT);
}

bool AndroidOpenGLESGameScreen::handleOnBackPressed()
{
    if(m_gameState == RUNNING)
    {
        onPause();

        return true;
    }
    
    return false;
}