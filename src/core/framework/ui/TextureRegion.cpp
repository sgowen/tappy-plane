//
//  TextureRegion.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "TextureRegion.h"

TextureRegion::TextureRegion(float x, float y, float regionWidth, float regionHeight, float textureWidth, float textureHeight)
{
	u1 = x / textureWidth;
    v1 = y / textureHeight;
    u2 = u1 + regionWidth / textureWidth;
    v2 = v1 + regionHeight / textureHeight;
}
