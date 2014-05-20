//
//  Font.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/12/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__Font__
#define __tappyplane__Font__

#ifdef TECHNE_GAMES_OPENGL_ES
class SpriteBatcher;
#include <string>
#include "Color.h"
#elif defined TECHNE_GAMES_DIRECT_3D
#include <SpriteBatch.h>
#include "DirectXMath.h"
#endif

#include <vector>
#include <memory>
#include "TextureRegion.h"

class Font
{
public:
	Font(int offsetX, int offsetY, int glyphsPerRow, int glyphWidth, int glyphHeight, int textureWidth, int textureHeight);
	
#ifdef TECHNE_GAMES_OPENGL_ES
    void renderText(SpriteBatcher &spriteBatcher, std::string &text, float x, float y, float width, float height, Color color, bool isCentered = false, bool isRightJustified = false);
#elif defined TECHNE_GAMES_DIRECT_3D
    void renderText(DirectX::SpriteBatch &spriteBatcher, ID3D11ShaderResourceView *fontShaderResourceView, std::string &text, float x, float y, float width, float height, DirectX::XMVECTORF32 &color, bool isCentered = false, bool isRightJustified = false);
#endif
	   
private:
    std::vector<std::unique_ptr<TextureRegion>> m_glyphs;
};

#endif /* defined(__tappyplane__Font__) */