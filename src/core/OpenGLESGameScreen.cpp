//
//  OpenGLESGameScreen.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 1/31/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "OpenGLESGameScreen.h"
#include "Vector2D.h"
#include "TouchEvent.h"
#include "OpenGLESRenderer.h"
#include "SpriteBatcher.h"
#include "PlaneDynamicGameObject.h"
#include "TextureRegion.h"
#include "Rectangle.h"
#include "GameButton.h"

extern "C"
{
#include "platform_gl.h"
#include "platform_log.h"
}

OpenGLESGameScreen::OpenGLESGameScreen() : GameScreen()
{
    
}

void OpenGLESGameScreen::platformInit()
{
    
}

void OpenGLESGameScreen::onSurfaceCreated(int width, int height)
{
	m_iDeviceScreenWidth = width;
	m_iDeviceScreenHeight = height;
    
    glViewport(0, 0, width, height);
	glScissor(0, 0, width, height);
    
	glLoadIdentity();
    
	glMatrixMode(GL_PROJECTION);
	glOrthof(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
    
	glLoadIdentity();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    m_renderer = std::unique_ptr<OpenGLESRenderer>(new OpenGLESRenderer());
}

void OpenGLESGameScreen::onSurfaceChanged(int width, int height)
{
	m_iDeviceScreenWidth = width;
	m_iDeviceScreenHeight = height;
    
    glViewport(0, 0, width, height);
	glScissor(0, 0, width, height);
}

void OpenGLESGameScreen::setDpDimensions(int dpWidth, int dpHeight)
{
	m_iDeviceScreenDpWidth = dpWidth;
	m_iDeviceScreenDpHeight = dpHeight;
}

void OpenGLESGameScreen::present()
{
    glClearColor(m_fColor, m_fColor, m_fColor, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    
    glEnable(GL_TEXTURE_2D);
    
    m_renderer->renderWorldBackground(*m_world);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    m_renderer->renderWorldForeground(*m_world, *m_glove, m_fTitleAlpha);
    
    if(m_gameState == GAME_OVER)
    {
        m_renderer->renderWorldGameOver(*m_world, *m_okButton, *m_leaderboardsButton, m_iBestScore);
    }
    
    glDisable(GL_BLEND);
    
    glDisable(GL_TEXTURE_2D);
}

void OpenGLESGameScreen::platformResume()
{
    // TODO
}

void OpenGLESGameScreen::platformPause()
{
    // TODO
}

bool OpenGLESGameScreen::handleOnBackPressed()
{
    return false;
}

#ifdef TECHNE_GAMES_OPENGL_ANDROID
void OpenGLESGameScreen::touchToWorld(TouchEvent &touchEvent)
{
    m_touchPoint->set((touchEvent.getX() / (float) m_iDeviceScreenWidth) * SCREEN_WIDTH, (1 - touchEvent.getY() / (float) m_iDeviceScreenHeight) * SCREEN_HEIGHT);
}
#elif defined TECHNE_GAMES_IOS
void OpenGLESGameScreen::touchToWorld(TouchEvent &touchEvent)
{
	m_touchPoint->set((touchEvent.getX() / (float) m_iDeviceScreenDpWidth) * SCREEN_WIDTH, (1 - touchEvent.getY() / (float) m_iDeviceScreenDpHeight) * SCREEN_HEIGHT);
}
#endif