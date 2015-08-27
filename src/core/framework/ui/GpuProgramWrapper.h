//
//  GpuProgramWrapper.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __nosfuratu__GpuProgramWrapper__
#define __nosfuratu__GpuProgramWrapper__

class GpuProgramWrapper
{
public:
    GpuProgramWrapper();
    
    virtual void bind() = 0;
    
    virtual void unbind() = 0;
};

#endif /* defined(__nosfuratu__GpuProgramWrapper__) */
