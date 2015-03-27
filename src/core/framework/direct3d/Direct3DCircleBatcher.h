//
//  Direct3DCircleBatcher.h
//  gowengamedev-framework
//
//  Created by Stephen Gowen on 11/16/14.
//  Copyright (c) 2015 Gowen Game Dev. All rights reserved.
//

#ifndef __gowengamedev__Direct3DCircleBatcher__
#define __gowengamedev__Direct3DCircleBatcher__

#include "CircleBatcher.h"

class Direct3DCircleBatcher : public CircleBatcher
{
public:
	Direct3DCircleBatcher();
    
    virtual void renderCircle(Circle &circle, Color &color);
    
    virtual void renderPartialCircle(Circle &circle, int arcDegrees, Color &color);

private:
	int m_iNumPoints;

	void endBatch();

	void addVertexCoordinate(float x, float y, float z, float r, float g, float b, float a, float u, float v);
};

#endif /* defined(__gowengamedev__Direct3DCircleBatcher__) */
