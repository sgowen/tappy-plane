//
//  IOSOpenGLESGameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 7/22/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "IOSOpenGLESGameScreen.h"
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

IOSOpenGLESGameScreen::IOSOpenGLESGameScreen(int pointsWidth, int pointsHeight) : OpenGLESGameScreen()
{
    m_iPointsWidth = pointsWidth;
    m_iPointsHeight = pointsHeight;
}

void IOSOpenGLESGameScreen::touchToWorld(TouchEvent &touchEvent)
{
    m_touchPoint->set((touchEvent.getX() / (float) m_iPointsWidth) * SCREEN_WIDTH, (((float)m_iPointsHeight - touchEvent.getY()) / (float) m_iPointsHeight) * SCREEN_HEIGHT);
}