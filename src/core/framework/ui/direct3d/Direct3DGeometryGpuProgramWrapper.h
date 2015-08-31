//
//  Direct3DGeometryGpuProgramWrapper.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/30/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Direct3DGeometryGpuProgramWrapper__
#define __gowengamedev__Direct3DGeometryGpuProgramWrapper__

#include "GpuProgramWrapper.h"

class Direct3DGeometryGpuProgramWrapper : public GpuProgramWrapper
{
public:
	Direct3DGeometryGpuProgramWrapper();

	virtual void bind();

	virtual void unbind();
};

#endif /* defined(__gowengamedev__Direct3DGeometryGpuProgramWrapper__) */
