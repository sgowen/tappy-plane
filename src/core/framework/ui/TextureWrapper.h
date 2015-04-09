//
//  TextureWrapper.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 9/25/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef gowengamedev_TextureWrapper_h
#define gowengamedev_TextureWrapper_h

#ifdef GGD_OPENGL_ES
extern "C"
{
#include "platform_gl.h"
}
#elif defined GGD_DIRECT_3D
#include <d3d11_1.h>
#endif

struct TextureWrapper
{
#ifdef GGD_OPENGL_ES
    GLuint texture;
    
    TextureWrapper(GLuint textureIn) : texture(textureIn)
    {
        // Empty
    }
#elif defined GGD_DIRECT_3D
    ID3D11ShaderResourceView *texture;
    
    TextureWrapper(ID3D11ShaderResourceView *textureIn) : texture(textureIn)
    {
        // Empty
    }
#endif
};

#endif /* defined(gowengamedev_TextureWrapper_h) */
