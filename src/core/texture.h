//
//  texture.h
//  tappyplane
//
//  Created by Stephen Gowen on 1/29/14.
//  Copyright (c) 2014 Techne Games. All rights reserved.
//

#ifndef Texture_H
#define Texture_H

#include "platform_gl.h"

GLuint load_texture(const GLsizei width, const GLsizei height, const GLenum type, const GLvoid* pixels);

#endif /* Texture_H */