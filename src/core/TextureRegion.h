//
//  TextureRegion.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef __tappyplane__TextureRegion__
#define __tappyplane__TextureRegion__

#ifdef TECHNE_GAMES_DIRECT_3D
#include <windows.h>
#endif

class TextureRegion
{
public:
    TextureRegion(float x, float y, float regionWidth, float regionHeight, float textureWidth, float textureHeight);
    
#ifdef TECHNE_GAMES_OPENGL_ES
    float u1, v1, u2, v2;
#elif TECHNE_GAMES_DIRECT_3D
    long left, top, right, bottom;
    RECT getSourceRECT();
#endif
};

#endif /* defined(__tappyplane__TextureRegion__) */