//
//  TopScreenRenderer.h
//  tappyplane
//
//  Created by Stephen Gowen on 8/25/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__TopScreenRenderer__
#define __tappyplane__TopScreenRenderer__

#include <memory>

#include <3ds.h>

class DSSpriteBatcher;
struct TextureWrapper;

class TopScreenRenderer
{
public:
    TopScreenRenderer(gfxScreen_t screen, int screenWidth, int screenHeight);

    void beginFrame();
    
    void render();

    void endFrame();

    void cleanUp();
    
private:
    gfxScreen_t m_screen;
    std::unique_ptr<DSSpriteBatcher> m_spriteBatcher;
    
    std::unique_ptr<TextureWrapper> m_topScreenTitleTexture;
};

#endif /* defined(__tappyplane__TopScreenRenderer__) */
