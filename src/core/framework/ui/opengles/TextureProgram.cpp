//
//  TextureProgram.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/4/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "TextureProgram.h"

TextureProgramStruct TextureProgram::getTextureProgram(GLuint program)
{
    return (TextureProgramStruct)
    {
        program,
        glGetUniformLocation(program, "u_MvpMatrix"),
        glGetAttribLocation(program, "a_Position"),
        glGetAttribLocation(program, "a_Color"),
        glGetAttribLocation(program, "a_TextureCoordinates"),
        glGetUniformLocation(program, "u_TextureUnit")
    };
}