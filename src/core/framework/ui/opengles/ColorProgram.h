//
//  ColorProgram.h
//  nosfuratu
//
//  Created by Stephen Gowen on 8/4/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __nosfuratu__ColorProgram__
#define __nosfuratu__ColorProgram__

extern "C"
{
#include "platform_gl.h"
}

typedef struct
{
    GLuint program;
    
    GLint u_mvp_matrix_location;
    GLint a_position_location;
    GLint a_color_location;
} ColorProgramStruct;

class ColorProgram
{
public:
    static ColorProgramStruct getColorProgram(GLuint program);
    
private:
    ColorProgram();
};

#endif /* defined(__nosfuratu__ColorProgram__) */
