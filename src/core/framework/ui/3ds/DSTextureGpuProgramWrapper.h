//
//  DSTextureGpuProgramWrapper.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __nosfuratu__DSTextureGpuProgramWrapper__
#define __nosfuratu__DSTextureGpuProgramWrapper__

#include "GpuProgramWrapper.h"

class DSTextureGpuProgramWrapper : public GpuProgramWrapper
{
public:
    DSTextureGpuProgramWrapper();
    
    virtual void bind();
    
    virtual void unbind();
};

#endif /* defined(__nosfuratu__DSTextureGpuProgramWrapper__) */
