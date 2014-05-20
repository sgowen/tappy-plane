//
//  OpenGLESRenderer.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__OpenGLESRenderer__
#define __tappyplane__OpenGLESRenderer__

#include "Renderer.h"

extern "C"
{
#include "platform_gl.h"
}

class Glove;

class OpenGLESRenderer : public Renderer
{
public:
    OpenGLESRenderer();
    
    virtual void renderWorldBackground(World &world);
    
    virtual void renderWorldForeground(World &world, Glove &glove, float titleAlpha);
    
    virtual void renderWorldGameOver(World &world, GameButton &okButton, GameButton &leaderboardsButton, int bestScore);
    
private:
    std::unique_ptr<SpriteBatcher> m_spriteBatcher;
    std::unique_ptr<SpriteBatcher> m_spriteBatcherWithColor;
    GLuint m_gameTexture;
    GLuint m_backgroundTexture;
    
    virtual void renderObstacle(Obstacle &obstacle);
    
    virtual void renderGameObject(GameObject &go, TextureRegion tr);
};

#endif /* defined(__tappyplane__OpenGLESRenderer__) */