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
#include "TriangleBatcher.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Font.h"
#include "GameButton.h"

#include <3ds.h>

#include <string.h>

DSGameScreen::DSGameScreen()
{
    m_renderer = std::unique_ptr<DSRenderer>(new DSRenderer());
}

void DSGameScreen::init()
{
    GameScreen::init();

    u8* fbb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    memset(fbb, 0, 240 * 400 * 3);
}

void DSGameScreen::touchToWorld(TouchEvent &touchEvent)
{
    // TODO
    m_touchPoint->set(5.8f, 9.0f);
}

void DSGameScreen::platformResume()
{
    // Empty
}

void DSGameScreen::platformPause()
{
    // Empty
}