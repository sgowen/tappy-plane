//
//  DummyGpuProgramWrapper.cpp
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/27/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#include "DummyGpuProgramWrapper.h"

DummyGpuProgramWrapper * DummyGpuProgramWrapper::getInstance()
{
    static DummyGpuProgramWrapper *instance = new DummyGpuProgramWrapper();
    return instance;
}

void DummyGpuProgramWrapper::bind()
{
    // TODO
}

void DummyGpuProgramWrapper::unbind()
{
    // TODO
}

DummyGpuProgramWrapper::DummyGpuProgramWrapper()
{
    // Hide Constructor for Singleton
}