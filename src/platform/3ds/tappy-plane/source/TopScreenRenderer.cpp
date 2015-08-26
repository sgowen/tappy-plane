//
//  TopScreenRenderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 8/25/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "TopScreenRenderer.h"
#include "DSSpriteBatcher.h"
#include "RectangleBatcher.h"
#include "LineBatcher.h"
#include "CircleBatcher.h"
#include "Font.h"
#include "TextureWrapper.h"
#include "GameConstants.h"
#include "ResourceConstants.h"
#include "SpriteBatcher.h"
#include "Circle.h"
#include "Color.h"
#include "TextureRegion.h"
#include "Assets.h"
#include "Vector2D.h"
#include "Font.h"
#include "TextureWrapper.h"
#include "Rectangle.h"
#include "PhysicalEntity.h"
#include "World.h"
#include "GameConstants.h"
#include "PuffCloud.h"
#include "PlanePhysicalEntity.h"
#include "Glove.h"
#include "GameButton.h"
#include "GameConstants.h"

#include <sstream>

#include <3ds.h>

#include <sf2d.h>

#include <stdio.h>

#include <string.h>

extern "C"
{
    extern const struct
    {
        unsigned int width;
        unsigned int height;
        unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
        unsigned char pixel_data[];
    } top_screen_title;
}

sf2d_texture *topScreenTitleTex;

TopScreenRenderer::TopScreenRenderer(gfxScreen_t screen, int screenWidth, int screenHeight) : m_screen(screen)
{
    m_spriteBatcher = std::unique_ptr<DSSpriteBatcher>(new DSSpriteBatcher(screen, screenWidth, screenHeight));

    topScreenTitleTex = sf2d_create_texture_mem_RGBA8(top_screen_title.pixel_data, top_screen_title.width, top_screen_title.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);

    m_topScreenTitleTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(topScreenTitleTex));
}

void TopScreenRenderer::beginFrame()
{
    sf2d_start_frame(m_screen, GFX_LEFT);
}

void TopScreenRenderer::render()
{
    static TextureRegion tr = TextureRegion(0.0f, 0.0f, 400.0f, 240.0f, 512.0f, 512.0f);
    m_spriteBatcher->beginBatch();
    m_spriteBatcher->drawSprite(GAME_WIDTH_1_2, GAME_HEIGHT_1_2, GAME_WIDTH, GAME_HEIGHT, 0, tr);
    m_spriteBatcher->endBatchWithTexture(*m_topScreenTitleTexture);
}

void TopScreenRenderer::endFrame()
{
    sf2d_end_frame();
}

void TopScreenRenderer::cleanUp()
{
    sf2d_free_texture(topScreenTitleTex);
}