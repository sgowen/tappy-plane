//
//  OpenGLESGameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "OpenGLESGameScreen.h"
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

OpenGLESGameScreen::OpenGLESGameScreen() : GameScreen()
{
    // Empty
}

void OpenGLESGameScreen::initGraphics(int screenWidth, int screenHeight)
{
    OGLESManager->init(screenWidth, screenHeight, GAME_WIDTH, GAME_HEIGHT);
    
    m_renderer = std::unique_ptr<OpenGLESRenderer>(new OpenGLESRenderer());
}

void OpenGLESGameScreen::platformResume()
{
    // Empty
}

void OpenGLESGameScreen::platformPause()
{
    // Empty
}
