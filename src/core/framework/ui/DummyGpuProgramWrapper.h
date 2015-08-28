//
//  DummyGpuProgramWrapper.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __nosfuratu__DummyGpuProgramWrapper__
#define __nosfuratu__DummyGpuProgramWrapper__

#include "GpuProgramWrapper.h"

class DummyGpuProgramWrapper : public GpuProgramWrapper
{
public:
    static DummyGpuProgramWrapper * getInstance();
    
    virtual void bind();
    
    virtual void unbind();
    
private:
    // ctor, copy ctor, and assignment should be private in a Singleton
    DummyGpuProgramWrapper();
    DummyGpuProgramWrapper(const DummyGpuProgramWrapper&);
    DummyGpuProgramWrapper& operator=(const DummyGpuProgramWrapper&);
};

#endif /* defined(__nosfuratu__DummyGpuProgramWrapper__) */
