//
//  IOS8OpenGLESGameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 7/22/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "IOS8OpenGLESGameScreen.h"
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

IOS8OpenGLESGameScreen::IOS8OpenGLESGameScreen(int screenWidth, int screenHeight, int pointsWidth, int pointsHeight) : IOSOpenGLESGameScreen(screenWidth, screenHeight, pointsWidth, pointsHeight)
{
    // Empty
}

void IOS8OpenGLESGameScreen::touchToWorld(TouchEvent &touchEvent)
{
    m_touchPoint->set((touchEvent.getX() / (float) m_iPointsWidth) * GAME_WIDTH, (1 - touchEvent.getY() / (float) m_iPointsHeight) * GAME_HEIGHT);
}