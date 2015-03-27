//
//  Direct3DRenderer.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/1/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __tappyplane__Direct3DRenderer__
#define __tappyplane__Direct3DRenderer__

#include "Renderer.h"

class Direct3DRenderer : public Renderer
{
public:
	Direct3DRenderer();

	virtual void clearScreenWithColor(float r, float g, float b, float a);

	virtual void beginFrame();

	virtual void endFrame();

	virtual void cleanUp();

private:
	void createInputLayoutForSpriteBatcher();

	void createInputLayoutForGeometryBatcher();
};

#endif /* defined(__tappyplane__Direct3DRenderer__) */