//
//  OpenGLESRenderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "OpenGLESRenderer.h"
#include "OpenGLESSpriteBatcher.h"
#include "OpenGLESRectangleBatcher.h"
#include "OpenGLESLineBatcher.h"
#include "OpenGLESCircleBatcher.h"
#include "Font.h"
#include "TextureWrapper.h"

extern "C"
{
#include "asset_utils.h"
#include "platform_gl.h"
}

OpenGLESRenderer::OpenGLESRenderer(int width, int height) : Renderer()
{
    m_spriteBatcher = std::unique_ptr<OpenGLESSpriteBatcher>(new OpenGLESSpriteBatcher());
    
    m_backgroundTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(load_png_asset_into_texture("background.png")));
    m_gameTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(load_png_asset_into_texture("game.png")));
}

void OpenGLESRenderer::clearScreenWithColor(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void OpenGLESRenderer::beginFrame()
{
    glEnable(GL_TEXTURE_2D);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void OpenGLESRenderer::endFrame()
{
    glDisable(GL_BLEND);
    
    glDisable(GL_TEXTURE_2D);
}

void OpenGLESRenderer::cleanUp()
{
    // TODO
}