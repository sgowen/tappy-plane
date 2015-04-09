//
//  OpenGLESGameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "macros.h"
#include "OpenGLESGameScreen.h"
#include "TouchEvent.h"
#include "Vector2D.h"
#include "OpenGLESRenderer.h"
#include "OpenGLESManager.h"
#include "GameConstants.h"
#include "Font.h"
#include "SpriteBatcher.h"
#include "RectangleBatcher.h"
#include "LineBatcher.h"
#include "CircleBatcher.h"
#include "GameListener.h"
#include "Rectangle.h"
#include "Circle.h"
#include "GameButton.h"

OpenGLESGameScreen::OpenGLESGameScreen(bool isRunningIOS8) : GameScreen()
{
    m_isRunningIOS8 = isRunningIOS8;
}

void OpenGLESGameScreen::onSurfaceCreated(int width, int height)
{
	m_iDeviceScreenWidth = width;
	m_iDeviceScreenHeight = height;
    
    OGLESManager->init(width, height);
    
    m_renderer = std::unique_ptr<OpenGLESRenderer>(new OpenGLESRenderer(width, height));
}

void OpenGLESGameScreen::onSurfaceChanged(int width, int height, int dpWidth, int dpHeight)
{
	m_iDeviceScreenWidth = width;
	m_iDeviceScreenHeight = height;
    m_iDeviceScreenDpWidth = dpWidth;
	m_iDeviceScreenDpHeight = dpHeight;
}

void OpenGLESGameScreen::touchToWorld(TouchEvent &touchEvent)
{
#ifdef GGD_OPENGL_ANDROID
    m_touchPoint->set((touchEvent.getX() / (float) m_iDeviceScreenWidth) * SCREEN_WIDTH, (1 - touchEvent.getY() / (float) m_iDeviceScreenHeight) * SCREEN_HEIGHT);
#elif defined GGD_IOS
    if(m_isRunningIOS8)
    {
        m_touchPoint->set((touchEvent.getX() / (float) m_iDeviceScreenDpWidth) * SCREEN_WIDTH, (1 - touchEvent.getY() / (float) m_iDeviceScreenDpHeight) * SCREEN_HEIGHT);
    }
    else
    {
        m_touchPoint->set((touchEvent.getY() / (float) m_iDeviceScreenDpHeight) * SCREEN_WIDTH, (touchEvent.getX() / (float) m_iDeviceScreenDpWidth) * SCREEN_HEIGHT);
    }
#endif
}

void OpenGLESGameScreen::platformResume()
{
    // Empty
}

void OpenGLESGameScreen::platformPause()
{
    // Empty
}

bool OpenGLESGameScreen::handleOnBackPressed()
{
    if(m_gameState == RUNNING)
    {
        onPause();
        
        return true;
    }
    
    return false;
}
