//
//  Renderer.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/13/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "Assets.h"
#include "Renderer.h"
#include "pch.h"

Renderer::Renderer()
{
    m_font = std::unique_ptr<Font>(new Font(FONT_TEXTURE_REGION_X, FONT_TEXTURE_REGION_Y, FONT_GLYPHS_PER_ROW, FONT_GLYPH_WIDTH, FONT_GLYPH_HEIGHT, GAME_TEXTURE_WIDTH, GAME_TEXTURE_HEIGHT));
}