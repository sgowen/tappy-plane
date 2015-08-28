//
//  OpenGLESGeometryGpuProgramWrapper.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __nosfuratu__OpenGLESGeometryGpuProgramWrapper__
#define __nosfuratu__OpenGLESGeometryGpuProgramWrapper__

#include "GpuProgramWrapper.h"
#include "ColorProgram.h"

class OpenGLESGeometryGpuProgramWrapper : public GpuProgramWrapper
{
public:
    OpenGLESGeometryGpuProgramWrapper(ColorProgramStruct colorProgramStruct);
    
    virtual void bind();
    
    virtual void unbind();
    
private:
    ColorProgramStruct m_colorProgram;
};

#endif /* defined(__nosfuratu__OpenGLESGeometryGpuProgramWrapper__) */
