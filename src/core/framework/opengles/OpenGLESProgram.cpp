//
//  OpenGLESProgram.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/15/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "OpenGLESProgram.h"

ColorProgram OpenGLESProgram::get_color_program(GLuint program)
{
    return (ColorProgram)
    {
        program,
        glGetUniformLocation(program, "u_MvpMatrix"),
        glGetAttribLocation(program, "a_Position"),
        glGetAttribLocation(program, "a_Color")
    };
}

TextureProgram OpenGLESProgram::get_texture_program(GLuint program)
{
    return (TextureProgram)
    {
        program,
        glGetUniformLocation(program, "u_MvpMatrix"),
        glGetAttribLocation(program, "a_Position"),
        glGetAttribLocation(program, "a_Color"),
        glGetAttribLocation(program, "a_TextureCoordinates"),
        glGetUniformLocation(program, "u_TextureUnit")
    };
}

OpenGLESProgram::OpenGLESProgram()
{
    // Hide Constructor for Singleton
}