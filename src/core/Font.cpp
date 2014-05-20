//
//  Font.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/12/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "Font.h"
#include "TextureRegion.h"

#ifdef TECHNE_GAMES_OPENGL_ES
#include "SpriteBatcher.h"
#elif defined TECHNE_GAMES_DIRECT_3D
#include "DirectXMath.h"
#include "RECTUtils.h"
#include <SpriteBatch.h>
#endif

Font::Font(int offsetX, int offsetY, int glyphsPerRow, int glyphWidth, int glyphHeight, int textureWidth, int textureHeight)
{
	int x = offsetX;
	int y = offsetY;

	for (int i = 0; i < 128; i++)
	{
		m_glyphs.push_back(std::unique_ptr<TextureRegion>(new TextureRegion(x, y, glyphWidth, glyphHeight, textureWidth, textureHeight)));

		x += glyphWidth;

		if (x == offsetX + glyphsPerRow * glyphWidth)
		{
			x = offsetX;
			y += glyphHeight;
		}
	}
}

#ifdef TECHNE_GAMES_OPENGL_ES
void Font::renderText(SpriteBatcher &spriteBatcher, std::string &text, float x, float y, float width, float height, Color color, bool isCentered, bool isRightJustified)
{
	if (isCentered)
	{
		int len = text.length();
		float result = width / 2;
		x -= len * result;
		x += width / 2;
	}
	else if(isRightJustified)
	{
		x -= (text.length() - 1) * width;
	}

	for (unsigned int i = 0; i < text.length(); i++)
	{
		int c = ((int) text.at(i)) - 16;

		if (c < 0 || c > 127)
		{
			continue;
		}

		spriteBatcher.drawSprite(x, y, width, height, 0, color, *m_glyphs[c]);

		x += width;
	}
}
#elif defined TECHNE_GAMES_DIRECT_3D
void Font::renderText(DirectX::SpriteBatch &spriteBatcher, ID3D11ShaderResourceView *fontShaderResourceView, std::string &text, float x, float y, float width, float height, DirectX::XMVECTORF32 &color, bool isCentered, bool isRightJustified)
{
	if (isCentered)
	{
		int len = text.length();
		float result = width / 2;
		x -= len * result;
		x += width / 2;
	}
	else if (isRightJustified)
	{
		x -= (text.length() - 1) * width;
	}

	for (unsigned int i = 0; i < text.length(); i++)
	{
		int c = ((int)text.at(i)) - 16;

		if (c < 0 || c > 127)
		{
			continue;
		}

		spriteBatcher.Draw(fontShaderResourceView, RECTUtils::getInstance()->getRECTForCoordinates(x, y, width, height, 0), &m_glyphs[c]->getSourceRECT(), color, 0, DirectX::XMFLOAT2(0, 0), DirectX::SpriteEffects_None, 0);

		x += width;
	}
}
#endif