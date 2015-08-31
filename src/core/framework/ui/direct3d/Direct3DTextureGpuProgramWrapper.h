//
//  Direct3DGpuProgramWrapper.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 8/30/15.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Direct3DTextureGpuProgramWrapper__
#define __gowengamedev__Direct3DTextureGpuProgramWrapper__

#include "GpuProgramWrapper.h"

class Direct3DTextureGpuProgramWrapper : public GpuProgramWrapper
{
public:
	Direct3DTextureGpuProgramWrapper();

	virtual void bind();

	virtual void unbind();
};

#endif /* defined(__gowengamedev__Direct3DTextureGpuProgramWrapper__) */
