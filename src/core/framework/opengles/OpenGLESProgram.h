//
//  OpenGLESProgram.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__OpenGLESProgram__
#define __gowengamedev__OpenGLESProgram__

extern "C"
{
#include "platform_gl.h"
#include "linmath.h"
}

typedef struct
{
    GLuint program;
    
    GLint u_mvp_matrix_location;
    GLint a_position_location;
    GLint a_color_location;
} ColorProgram;

typedef struct
{
    GLuint program;
    
    GLint u_mvp_matrix_location;
    GLint a_position_location;
    GLint a_color_location;
    GLint a_texture_coordinates_location;
    GLint u_texture_unit_location;
} TextureProgram;

class OpenGLESProgram
{
public:
    static ColorProgram get_color_program(GLuint program);
    
    static TextureProgram get_texture_program(GLuint program);
    
private:
    OpenGLESProgram();
};

#endif /* defined(__gowengamedev__OpenGLESProgram__) */
