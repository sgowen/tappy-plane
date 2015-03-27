//
//  Direct3DSpriteBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 9/22/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Direct3DSpriteBatcher__
#define __gowengamedev__Direct3DSpriteBatcher__

#include "SpriteBatcher.h"
#include <vector>

class Direct3DSpriteBatcher : public SpriteBatcher
{
public:
	Direct3DSpriteBatcher();
    
	virtual void beginBatch();

	virtual void endBatchWithTexture(TextureWrapper &textureWrapper);
    
	virtual void drawSprite(float x, float y, float width, float height, float angle, TextureRegion tr);
    
	virtual void drawSprite(float x, float y, float width, float height, float angle, Color &color, TextureRegion tr);
    
protected:
	virtual void drawSprite(float x, float y, float width, float height, TextureRegion tr);

	virtual void drawSprite(float x, float y, float width, float height, Color &color, TextureRegion tr);

private:
    void addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a, float u, float v);
};

#endif /* defined(__gowengamedev__Direct3DSpriteBatcher__) */