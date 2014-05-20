//
//  TextureRegion.cpp
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#include "pch.h"
#include "TextureRegion.h"

TextureRegion::TextureRegion(float x, float y, float regionWidth, float regionHeight, float textureWidth, float textureHeight)
{
#ifdef TECHNE_GAMES_OPENGL_ES
    u1 = x / textureWidth;
    v1 = y / textureHeight;
    u2 = u1 + regionWidth / textureWidth;
    v2 = v1 + regionHeight / textureHeight;
#elif defined TECHNE_GAMES_DIRECT_3D
    left = x;
    top = y;
    right = x + regionWidth;
    bottom = y + regionHeight;
#endif
}

#ifdef TECHNE_GAMES_DIRECT_3D
RECT TextureRegion::getSourceRECT()
{
	RECT sourceRECT = { left, top, right, bottom };
    return sourceRECT;
}
#endif