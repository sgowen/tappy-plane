//
//  TriangleBatcher.h
//  tappyplane
//
//  Created by Stephen Gowen on 8/20/15.
//  Copyright (c) 2015 Techne Games. All rights reserved.
//

#ifndef __tappyplane__TriangleBatcher__
#define __tappyplane__TriangleBatcher__

#include "Color.h"

class Triangle;

class TriangleBatcher
{
public:
    TriangleBatcher(bool isFill);
    
    virtual void beginBatch() = 0;
    
    virtual void endBatch() = 0;
    
    void renderTriangle(Triangle &triangle, Color &color);
    
    virtual void renderTriangle(float x1, float y1, float x2, float y2, float x3, float y3, Color &color) = 0;
    
protected:
    int m_iNumTriangles;
    bool m_isFill;
};

#endif /* defined(__tappyplane__TriangleBatcher__) */
