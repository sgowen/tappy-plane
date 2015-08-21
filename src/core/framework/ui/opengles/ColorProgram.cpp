//
//  ColorProgram.cpp
//  nosfuratu
//
//  Created by Stephen Gowen on 8/4/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "ColorProgram.h"

ColorProgramStruct ColorProgram::getColorProgram(GLuint program)
{
    return (ColorProgramStruct)
    {
        program,
        glGetUniformLocation(program, "u_MvpMatrix"),
        glGetAttribLocation(program, "a_Position"),
        glGetAttribLocation(program, "a_Color")
    };
}