//
//  texture.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 2/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef Texture_H
#define Texture_H

#include "platform_gl.h"

GLuint load_texture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid* pixels);

#endif /* Texture_H */