//
//  DSRenderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "DSRenderer.h"
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
        unsigned int bytes_per_pixel;
        unsigned char pixel_data[];
    } game;

    extern const struct
    {
        unsigned int width;
        unsigned int height;
        unsigned int bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */
        unsigned char pixel_data[];
    } background;
}

sf2d_texture *backgroundTex;
sf2d_texture *gameTex;

DSRenderer::DSRenderer(gfxScreen_t screen, int screenWidth, int screenHeight) : Renderer()
{
    m_spriteBatcher = std::unique_ptr<DSSpriteBatcher>(new DSSpriteBatcher(screen, screenWidth, screenHeight));

    sf2d_init(GAME_WIDTH, GAME_HEIGHT, GAME_WIDTH, GAME_HEIGHT);

    backgroundTex = sf2d_create_texture_mem_RGBA8(background.pixel_data, background.width, background.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
    gameTex = sf2d_create_texture_mem_RGBA8(game.pixel_data, game.width, game.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);

    m_backgroundTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(backgroundTex));
    m_gameTexture = std::unique_ptr<TextureWrapper>(new TextureWrapper(gameTex));
}

DSRenderer::~DSRenderer()
{
    cleanUp();
}

void DSRenderer::clearScreenWithColor(float r, float g, float b, float a)
{
    sf2d_set_clear_color(RGBA8((int) (r * 255), (int) (g * 255), (int) (b * 255), (int) (a * 255)));
}

void DSRenderer::beginFrame()
{
    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
}

void DSRenderer::endFrame()
{
    sf2d_end_frame();

    sf2d_swapbuffers();
}

void DSRenderer::cleanUp()
{
    sf2d_free_texture(backgroundTex);
    sf2d_free_texture(gameTex);

    sf2d_fini();
}